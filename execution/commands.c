/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:07:16 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/09 15:23:36 by otitebah         ###   ########.fr       */
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
			// printf("PATH ---> [** %s **]\n", spl[1]);
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
		perror((p)->args[0]);
	// printf("%s\n", find_path);
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
		// close(p->infile);
		// close(p->outfile);
		// exit (0);
	}
}

void	execute_cmd_pipe(t_args *p, t_list *saving_expo, char **env)
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
		// write(2, "+++++++++++++++", 16);	
		perror((p)->args[0]);
	}
	// printf("%s\n", find_path);
	spl_path = ft_split(find_path, ':');
	cmd = ft_strjoin("/", p->args[0]);
	i = 0;
	while (spl_path[i])
	{
		command = ft_strjoin(spl_path[i], cmd);
		if (access(command, X_OK) != -1)
		{
			// write(2, "\n***execve[now]***\n", 19);
			execve(command, (p)->args, env);
		}
		i++;
	}
	ft_putstr_fd(*p->args, 2);
	write (2, ": command not found\n", 21);
	// exit(0);
}

//*******************************************************************************************

// void	ft_child_process(t_args *p, t_list *saving_expo, int pid, int *fd, char **env)
// {
// 	if (pid == 0)
// 	{
// 		if (p->outfile != 1)
// 			dup2(p->outfile, 1);
// 		else if (p->next)
// 		{
// 			dup2(fd[1], 1);
// 			close (fd[1]);
// 		}
// 		close(fd[1]);
// 		execute_cmd_pipe(saving_expo, env);
// 	}
// }

// void	multiplePipes(t_list *saving_expo, t_args *p, int *fd, int *pid, int *stdin, char **env)
// {
// 	puts("----in multiplePipe function----");
// 	if (p->infile < 2)
// 	{
// 		puts("there is no infile");
// 		close(fd[0]);
// 		close(fd[1]);
// 	}
// 	if (p->infile != 0)
// 	{
// 		puts("there is infile");		
// 		dup2(p->infile, 0);
// 	}
// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(1);
// 	}
// 	*pid = fork();
// 	ft_child_process(p, saving_expo, *pid, fd, env);
// 	close (fd[1]);
// }

void	Implement_Cmnd(t_list *saving_expo, t_args *p, char **env)
{
	t_args	*tmp;
	int		i;
	(void)saving_expo;
	(void)env;
	
	tmp = p;
	saving_expo->cmds = 0;
	
	while (tmp)
	{
		tmp = tmp->next;
		saving_expo->cmds++;
	}
	tmp = p;
	
	i = 0;
	if (saving_expo->cmds == 1)
		execute_cmd(p, saving_expo, env);
	else
	{
		i = 0;
		while (i < saving_expo->cmds)
		{
			if (tmp->infile != 0)
				dup2(tmp->infile, 0);
			if (pipe(saving_expo->fd) == -1)
			{
				perror("pipe failed");
				exit(0);
			}
			int id = fork();
			printf("id == %d\n", id);
			if (id == 0)
			{
				if (tmp->infile == 1)
				{
					dup2(saving_expo->tmp, STDIN_FILENO);
					close (saving_expo->tmp);
				}
				if (tmp->outfile != 1)
					dup2(tmp->outfile, 1);
				else if(tmp->next)
					dup2(saving_expo->fd[1], 1);
				close (saving_expo->fd[0]);
				close(saving_expo->fd[1]);
				execute_cmd_pipe(tmp, saving_expo, env);
			}
			dup2(saving_expo->fd[0], 0);
			close(saving_expo->fd[1]);
			close(saving_expo->fd[0]);
			tmp = tmp->next;
			i++;
		}
		close(0);
		dup2(saving_expo->tmp, 0);
	}
	
}







	// char	**spl_path;
	// char	*command;
	// char	*cmd;
	// char	*find_path;
	// int		i;
	// int		fd;
	// (void)env;

	// find_path = search_path(saving_expo, "PATH");
	// if (!find_path)
	// 	perror(p->args[0]);
	// // printf("%s\n", find_path);
	// spl_path = ft_split(find_path, ':');
	// cmd = ft_strjoin("/", p->args[0]);
	// i = 0;
	// fd = fork();
	// if (fd == 0)
	// {
	// 	while (spl_path[i])
	// 	{
	// 		command = ft_strjoin(spl_path[i], cmd);
	// 		if (access(command, X_OK) != -1)
	// 			execve(command, p->args, env);
	// 		i++;
	// 	}
	// 	// close (fd);
	// }
	// wait(NULL);





	