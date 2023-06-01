/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:07:16 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/31 14:27:34 by otitebah         ###   ########.fr       */
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
		while (spl_path[i])
		{
			command = ft_strjoin(spl_path[i], cmd);
			if (access(command, X_OK) != -1)
				execve(command, (p)->args, env);
			i++;
		}
		// close (fd);
	}
	wait(NULL);
}

void	Implement_Cmnd(t_list *saving_expo, t_args *p, char **env)
{
	t_args *tmp;
	int pipeIndex = 0;
	int **fd;
	int		i;
	
	tmp = p;
	while (tmp->next)   // this while for getting the number of pipes
	{
		pipeIndex++;
		tmp = tmp->next;
	}

	
	if (pipeIndex == 0 && tmp->infile < 2 && tmp->outfile > 2) //bhala endi cat > "smiya d file"
	{
		int only_out;
		only_out = fork();
		if (only_out == 0)
		{
			dup2(p->outfile, 1);
			execute_cmd(p, saving_expo, env);
			close (p->outfile);
		}
		wait (NULL);
	}

	else if (pipeIndex == 0 && tmp->infile > 2 && tmp->outfile < 2)
	{
		int only_in;
		only_in = fork();
		if (only_in == 0)
		{
			dup2(p->infile, 0);
			execute_cmd(p, saving_expo, env);
			close (p->infile);
		}
		wait (NULL);
	}
	//👇finissiio khadma kat7annnn
	if (pipeIndex == 0 && tmp->infile > 2 && tmp->outfile > 2)
	{
		puts("-----------");
		printf("you have %d pipes\n", pipeIndex);
		puts("-----------");
		//hna zid ila maknt tachi pipe "< sab cat > out" o kan dakchi li dekhel user haka dayer
		int k;
		k = fork();
		if (k == 0)
		{
			if (p->infile > 2)
			{
				// puts("tmp->infile > 2");
				dup2(p->infile, 0);
				close(p->infile);
			}
			if (p->outfile > 2)
			{
				// puts("tmp->outfile > 2");
				dup2(p->outfile, 1);
				close(p->outfile);
			}
			execute_cmd(p, saving_expo, env);	
		}
		wait (NULL);
	}
	else if(pipeIndex == 0 && tmp->infile < 2 && tmp->outfile < 2)
	{
		puts("------------");
		puts("pipeIndex == 0 && tmp->infile < 2 && tmp->outfile < 2");
		puts("------------");
		execute_cmd(p, saving_expo, env);	
	}
		
	// else
	// {
	// 	fd = (int **)malloc(sizeof(int *) * pipeIndex);
	// 	i = 1;
	// 	while (pipeIndex > i)
	// 	{
	// 		fd[i] = (int *)malloc(sizeof(int) * 2);
	// 		i++;
	// 	}
	// 	i = 1;
	// 	while (i < pipeIndex)
	// 	{
	// 		if (pipe(fd[i]) == -1)  // set up pipes
	// 		{
	// 			perror("failed creation pipe");
	// 			return ;	
	// 		}
	// 		i++;
	// 	}
	// 	tmp = p;
	// 	i = 0;
	// 	while (tmp->next)
	// 	{
	// 		int f;
	// 		f = fork();
	// 		if (f == 0)
	// 		{
	// 			if (tmp->infile > 2) //hna kayn infile
	// 			{
	// 				puts("tmp->infile > 2");
	// 				dup2(tmp->infile ,0);
	// 				close(tmp->infile);
	// 			}
	// 			else if (tmp->infile <= 2 && i > 1) //hna
	// 			{
	// 				puts("tmp->infile <= 2 && tmp->next");
	// 				dup2(fd[i][0], fd[i - 1][0]);
	// 				close(fd[i][0]);
	// 			}
	// 			printf("\ntmp->outfile == %d\n\n", tmp->outfile);
	// 			if (tmp->outfile > 2)
	// 			{
	// 				puts("tmp->outfile > 2");
	// 				dup2(tmp->outfile, 1);
	// 				close(tmp->outfile);
	// 			}
	// 			else if(tmp->outfile < 3 && i > 1)
	// 			{
	// 				puts("tmp->outfile < 3 && tmp->next");
	// 				dup2(fd[i][1], fd[i - 1][1]);
	// 				close(fd[i][1]);
	// 			}
	// 			else if (tmp->outfile == 1 && i == 0)
	// 			{
	// 				dup2(tmp->outfile, 1);
	// 				close(tmp->outfile);
	// 			}
	// 			execute_cmd(p, saving_expo, env);
	// 			wait (NULL);
	// 		}
	// 		i++;
	// 		tmp = tmp->next;
	// 	}
	// }
	
	
	
	// puts("\n");
	// puts("\n");
	// puts("\n");
	// while (p)
	// {
	// 		int t = 0;
	// 		while (p->args[t])
	// 			printf("args = %s\n", p->args[t++]);
	// 		printf("infile = %d\n", p->infile);
	// 		printf("outfile = %d\n", p->outfile);
	// 		printf("****************\n");
	// 		p = p->next;
	// }

	
	// exit(0);
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





	