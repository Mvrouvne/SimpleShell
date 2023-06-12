/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:07:16 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/12 21:20:08 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*search_path(t_list *saving_expo, char *node)
{
	t_list	*tmp;
	char **spl;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node))) == 0)
		{
			spl = ft_split(tmp->value, '=');
			return (spl[1]);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	check_slash(t_args *p, char **env)
{
	if (p->args[0][0] == '/')
	{
		execve(p->args[0], p->args, env);
		ft_putstr_fd(*p->args, 2);
		write (2, ": command not found\n", 21);
		return ;
	}
}

void	child_exec_solo_cmd(t_args *p, char	**spl_path, char **env, char *cmd)
{
	char	*command;
	int		i;
	int	fd;
	
	i = 0;
	fd = fork();
	if (fd == 0)
	{
		check_slash(p, env);
		dup2(p->infile, 0);
		dup2(p->outfile, 1);
		while (spl_path[i])
		{
			command = ft_strjoin(spl_path[i], cmd);
			if (access(command, X_OK) != -1)
				execve(command, (p)->args, env);
			i++;
		}
		close(p->infile);
		close(p->outfile);
		ft_putstr_fd(*p->args, 2);
		write (2, ": command not found\n", 21);
	}
}

void execute_cmd(t_args *p, t_list *saving_expo, char **env)
{
	char	*cmd;
	char	*find_path;
	char	**spl_path;

	find_path = search_path(saving_expo, "PATH");
	if (!find_path)
	{		
		ft_putstr_fd(*p->args, 2);
		write (2, ": command not found\n", 21);
		return ;
	}
	spl_path = ft_split(find_path, ':');
	cmd = ft_strjoin("/", p->args[0]);
	child_exec_solo_cmd(p, spl_path, env, cmd);
}

int	execute_cmd_pipe(t_args *p, t_list *saving_expo, char **env)
{
	char	**spl_path;
	char	*command;
	char	*cmd;
	char	*find_path;
	int		i;

	find_path = search_path(saving_expo, "PATH");
	if (!find_path)
	{
		ft_putstr_fd(*p->args, 2);
		write (2, ": command not found\n", 21);
		return (1);
	}
	check_slash(p, env);
	spl_path = ft_split(find_path, ':');
	cmd = ft_strjoin("/", p->args[0]);
	i = 0;
	while (spl_path[i])
	{
		command = ft_strjoin(spl_path[i], cmd);
		if (access(command, X_OK) != -1)
			execve(command, (p)->args, env);
		i++;
	}
	ft_putstr_fd(*p->args, 2);
	write (2, ": command not found\n", 21);
	exit (1);
}

void child_process(t_args *tmp, t_pipe *pipes, t_list *saving_expo, char **env)
{
	if (tmp->infile != 0)
		dup2(tmp->infile, 0);
	if (pipe(pipes->fd) == -1)
	{
		perror("pipes failed");
		exit(0);
	}
	int id = fork();
	if (id == 0)
	{
		if (tmp->infile == 1)
		{
			dup2(pipes->tmp, STDIN_FILENO);
			close (pipes->tmp);
		}
		if (tmp->outfile != 1)
			dup2(tmp->outfile, 1);
		else if(tmp->next)
			dup2(pipes->fd[1], 1);
		close (pipes->fd[0]);
		close(pipes->fd[1]);
		if (execute_cmd_pipe(tmp, saving_expo, env) == 1)
			exit(1);
	}
}

void	Implement_Cmnd(t_list *saving_expo, t_args *p, char **env, t_pipe *pipes)
{
	t_args	*tmp;
	int		i;
	
	tmp = p;
	pipes->cmds = 0;
	while (tmp)
	{
		tmp = tmp->next;
		pipes->cmds++;
	}
	tmp = p;
	if (pipes->cmds == 1)
		execute_cmd(p, saving_expo, env);
	else
	{
		i = 0;
		while (i < pipes->cmds)
		{
			child_process(tmp, pipes, saving_expo, env);
			dup2(pipes->fd[0], 0);
			close(pipes->fd[1]);
			close(pipes->fd[0]);
			tmp = tmp->next;
			i++;
		}
		close(0);
		dup2(pipes->tmp, 0);
	}
}
