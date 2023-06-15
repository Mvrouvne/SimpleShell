/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:07:16 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/15 11:48:32 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
		exit(0) ;
	}
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
		return (0);
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
	return(0);
	// exit (1);
}

void child_process(t_args *tmp, t_pipe *pipes, t_data *lst, char **env)
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
        puts("fork dyal pipes");
        if(tmp->args[0] == NULL)
            exit(0);
		if (check_if_builtins(tmp) == 1 && tmp->next)
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
			builtins(tmp, &lst->saving_env, &lst->saving_expo);
			close (pipes->fd[0]);
			close(pipes->fd[1]);
			exit(1);
		}
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
		if (execute_cmd_pipe(tmp, lst->saving_expo, env) == 0)
			exit(1);
	}
}

int	check_if_builtins(t_args *p)
{
	if (!ft_strcmp(p->args[0], "echo"))
		return (1);
	else if (!ft_strcmp(p->args[0], "pwd"))
		return (1);
	else if (!ft_strcmp(p->args[0], "cd"))
		return (1);
	else if (!ft_strcmp(p->args[0], "env"))
		return (1);
	else if (!ft_strcmp(p->args[0], "export"))
		return (1);
	else if (!ft_strcmp(p->args[0], "unset"))
		return (1);
	else if (!ft_strcmp(p->args[0], "exit"))
		return (1);
	return (0);
}

void	Implement_Cmnd(t_data *lst, t_args *p, char **env_copy, t_pipe *pipes)
{
	t_args	*tmp;
	int		i;
	(void)env_copy;
	(void)lst;

	if (!p->args[0])
		return ;
	tmp = p;
	pipes->cmds = 0;
	while (tmp)
	{
		tmp = tmp->next;
		pipes->cmds++;
	}
	tmp = p;
	if (pipes->cmds == 1)
	{
		if (check_if_builtins(p) == 1)
			builtins(p, &lst->saving_env, &lst->saving_expo);
		else
			child_exec_solo_cmd(p, lst->saving_expo, env_copy);
	}
	else
	{
		i = 0;
		while (i < pipes->cmds)
		{
			child_process(tmp, pipes, lst, env_copy);
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