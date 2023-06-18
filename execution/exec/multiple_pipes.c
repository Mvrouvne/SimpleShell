/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:17:05 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/18 15:45:10 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"



void	check_slash(t_args *p, char **env)
{
	extern int	g_exit_status;

	if (p->args[0][0] == '/')
	{
		execve(p->args[0], p->args, env);
		ft_putstr_fd(*p->args, 2);
		write (2, ": command not founddd\n", 23);
		g_exit_status = 127;
		exit(g_exit_status) ;
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
	if (!ft_strcmp(p->args[0], "./minishell"))
		execve(p->args[0], (p)->args, env);
	else if (p->args[0][0] == '.')
	{
		ft_error("", p->args[0], "command not found", 1);
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
		free (command);
		i++;
	}
	ft_putstr_fd(*p->args, 2);
	write (2, ": command not foundddd\n", 23);
	return(0);
}

void child_builtins(t_args *tmp, t_pipe *pipes, t_data *lst)
{
	extern int g_exit_status;
	
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
	g_exit_status = 0;
	exit(g_exit_status);
}

void child_not_builtins(t_args *tmp, t_pipe *pipes)
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
}

void child_process(t_args *tmp, t_pipe *pipes, t_data *lst, char **env)
{
	extern	int g_exit_status;

	if (tmp->infile != 0)
		dup2(tmp->infile, 0);
	if (pipe(pipes->fd) == -1)
	{
		perror("pipes failed");
		exit(0);
	}
	lst->pid[lst->id] = fork();
	if (lst->pid[lst->id] == 0)
	{
		if (check_if_builtins(tmp) == 1)
			child_builtins(tmp, pipes, lst);
		child_not_builtins(tmp, pipes);
		if (execute_cmd_pipe(tmp, lst->saving_expo, env) == 0)
		{
			g_exit_status = 127;
			exit(g_exit_status);
		}
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

	// if (!p->args[0])
	// 	return ;
	// lst->pid = malloc(sizeof(t_status));
	// system("leaks minishell");
	pipes->cmds = 0;
	tmp = p;
	while (tmp)
	{
		tmp = tmp->next;
		pipes->cmds++;
	}
	tmp = p;
	lst->id = 0;
	lst->pid = malloc(sizeof(int) * pipes->cmds);
	if (pipes->cmds == 1)
	{
		if (!tmp->args[0])
			return ;
		if (check_if_builtins(p) == 1)
			builtins(p, &lst->saving_env, &lst->saving_expo);
		else
		{
			child_exec_solo_cmd(p, lst->saving_expo, env_copy, lst);
			lst->id++;
		}
	}
	else
	{
		i = 0;
		while (p && i < pipes->cmds)
		{
			if (!tmp->args[0])
				i++;
			else
			{
				child_process(tmp, pipes, lst, env_copy);
				lst->id++;
				dup2(pipes->fd[0], 0);
				close(pipes->fd[1]);
				close(pipes->fd[0]);
				i++;
				
			}
			tmp = tmp->next;
		}
		free(lst->pid);
		close(0);
		dup2(pipes->tmp, 0);
	}
}
