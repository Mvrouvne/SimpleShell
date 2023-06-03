/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:07:16 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/03 14:44:30 by otitebah         ###   ########.fr       */
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

void	Implement_Cmnd(t_list *saving_expo, t_args *p, char **env)
{
	t_args *tmp;
	int pipeIndex = 0;
	// int **fd;
	// int		i;
	
	tmp = p;
	while (tmp->next)   // this while for getting the number of pipes
	{
		pipeIndex++;
		tmp = tmp->next;
	}
	printf("the number of pipes is : %d\n", pipeIndex);
	
	if (pipeIndex == 0 && tmp->infile < 2 && tmp->outfile < 2) //bhala endi cat > "smiya d file"
		execute_cmd(p, saving_expo, env);
	else if (pipeIndex == 0 && tmp->infile > 2 && tmp->outfile < 2)
		execute_cmd(p, saving_expo, env);
	else if (pipeIndex == 0 && tmp->infile < 2 && tmp->outfile > 2)
		execute_cmd(p, saving_expo, env);
	else if (pipeIndex == 0 && tmp->infile > 2 && tmp->outfile > 2)
		execute_cmd(p, saving_expo, env);
	// else if (pipeIndex > 1)
	// {
		
	// }
	
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





	