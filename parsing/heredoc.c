/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:45:22 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/22 13:12:52 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handler2(int num)
{
	(void) num;
	printf("\n");
	exit (10);
}

int	heredoc3(int status, int id, int fd[2])
{
	extern int	g_exit_status;

	waitpid(id, &status, 0);
	if (WEXITSTATUS(status) == 10)
	{
		close (fd[1]);
		g_exit_status = 1;
		return (g_exit_status);
	}
	else if (WEXITSTATUS(status) == 20)
	{
		close (fd[1]);
		g_exit_status = 0;
		return (g_exit_status);
	}
	close (fd[1]);
	return (0);
}

int	heredoc(t_args *args, char *delimiter, t_env *env_parse, t_token *lst)
{
    char    *line = NULL;
    char    *str = NULL;
    int     fd[2];
	int		x;
	int		id;
	int		status;
	extern int	g_exit_status;
    
    x = 0;
	status = 0;
   	pipe(fd);
	args->infile = fd[0];
	args->outfile = 1;
	id = fork();
	signal(SIGINT, SIG_IGN);
	if (id == 0)
	{
		// system("leaks minishell");
		// while (1);
		signal(SIGINT, handler2);
		while (1)
		{
			line = readline("> ");
			if (line && line[0] == '\n')
				continue;
			else if (!line || (!(ft_strcmp(line, delimiter))))
			{
				free (line);
				close (fd[1]);
				exit (20);
			}
			else if (lst && (!(lst->av_quotes)))
			{
				str = heredoc_expand(line, env_parse);
				write(fd[1], str, ft_strlen(str));
				write (fd[1], "\n", 1);	
				free (str);
			}
			else
			{
				write(fd[1], line, ft_strlen(line));
				write (fd[1], "\n", 1);
			}
			free (line);
		}
	}
	return (heredoc3(status, id, fd));
    return (0);
}
