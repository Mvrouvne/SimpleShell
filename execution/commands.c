/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:07:16 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/11 16:45:10 by otitebah         ###   ########.fr       */
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
void execute_cmd(t_args *p, t_list *saving_expo, char **env)
{
	char	**spl_path;
	char	*command;
	char	*cmd;
	char	*find_path;
	int		i;
	int		fd;
	(void)env;

	find_path = search_path(saving_expo, "PATH");
	if (!find_path)
	{		
		ft_putstr_fd(*p->args, 2);
		write (2, ": command not found\n", 21);
		return ;
	}
	spl_path = ft_split(find_path, ':');
	cmd = ft_strjoin("/", p->args[0]);
	i = 0;
	fd = fork();
	if (fd == 0)
	{
		dup2(p->infile, 0);
		dup2(p->outfile, 1);
		while (spl_path[i])
		{
			command = ft_strjoin(spl_path[i], cmd);
			if (access(command, X_OK) != -1)
				execve(command, (p)->args, env);
			i++;
		}
		ft_putstr_fd(*p->args, 2);
		write (2, ": command not found\n", 21);
	}
}

int	execute_cmd_pipe(t_args *p, t_list *saving_expo, char **env)
{
	char	**spl_path;
	char	*command;
	char	*cmd;
	char	*find_path;
	int		i;
	// int		fd;
	(void)env;

	find_path = search_path(saving_expo, "PATH");
	if (!find_path)
	{
		ft_putstr_fd(*p->args, 2);
		write (2, ": command not found\n", 21);
		return (1);
	}
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

//*******************************************************************************************



void	Implement_Cmnd(t_list *saving_expo, t_args *p, char **env, t_pipe *pipes)
{
	t_args	*tmp;
	int		i;
	(void)saving_expo;
	(void)env;
	
	tmp = p;
	pipes->cmds = 0;
	while (tmp)
	{
		tmp = tmp->next;
		pipes->cmds++;
	}
	tmp = p;
	
	i = 0;
	if (pipes->cmds == 1)
		execute_cmd(p, saving_expo, env);
	else
	{
		i = 0;
		while (i < pipes->cmds)
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
				{
					write (2, "hana\n", 5);
					exit(0);
				}
			}
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
