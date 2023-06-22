/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:17:05 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/22 15:01:12 by otitebah         ###   ########.fr       */
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
	check_slash(p, env);
	spl_path = ft_split(find_path, ':');
	free(find_path);
	cmd = ft_strjoin("/", p->args[0]);
	i = 0;
	if(p->args[0][0] == '.' || p->args[0][0] == '/')
		execve(p->args[0], (p)->args, env);
	while (spl_path[i])
	{
		command = ft_strjoin(spl_path[i], cmd);
		if (access(command, X_OK) != -1)
		{
			free(cmd);
			ft_free(spl_path);
			execve(command, (p)->args, env);
		}
		free (command);
		i++;
	}
	free(command);
	free(cmd);
	ft_free(spl_path);
	ft_putstr_fd(*p->args, 2);
	write (2, ": command not foundddd\n", 23);
	return(0);
}


void	Implement_Cmnd(t_data *lst, t_args *p, char **env_copy, t_pipe *pipes)
{
	t_args	*tmp;
	int		i;

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
		close(0);
		dup2(pipes->tmp, 0);
	}
}
