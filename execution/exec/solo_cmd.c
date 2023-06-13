/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:14:18 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/13 16:46:05 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	child_exec_solo_cmd(t_args *p, t_list *saving_expo, char **env_copy)
{
	int		i;
	int fd;
	
	i = 0;
	fd = fork();
	printf("AM HREER\n");
	if (fd == 0)
	{
		printf("%d\n", p->infile);
		puts("awtani");
		check_slash(p, env_copy);
		dup2(p->infile, 0);
		dup2(p->outfile, 1);
		if (p->infile != 0)
			close(p->infile);
		if (p->outfile != 1)
			close(p->outfile);
		if(execute_cmd(p,saving_expo, env_copy) == 0)
			exit(0);
	}
	// close(0);
}

int	execute_cmd(t_args *p, t_list *saving_expo, char **env_copy)
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
	spl_path = ft_split(find_path, ':');
	cmd = ft_strjoin("/", p->args[0]);
    i = 0;
	while (spl_path[i])
	{
		command = ft_strjoin(spl_path[i], cmd);
		if (access(command, X_OK) != -1)
			execve(command, (p)->args, env_copy);
		i++;
	}
	ft_putstr_fd(*p->args, 2);
	write (2, ": command not found\n", 21);
	return(0);
}