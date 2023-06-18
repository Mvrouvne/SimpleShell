/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:45:22 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/18 16:33:01 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handler2(int num)
{
	(void) num;
	printf("\n");
	// while (wait(NULL) != -1)
	exit (10);
}

char	*heredoc_expand(char *line, t_env *env_parse, t_token *lst)
{
	(void) lst;
	char	*to_expand = NULL;
    int     x;
	int		y;
	int		z;
	int		j;
	int		i;
	char 	*str;
	char 	*env_split;

	str = NULL;
	env_split = NULL;
	env_split = malloc(sizeof(char));
	env_split[0] = '\0';
    x = 0;
	z = 0;
	y = 0;
	i = 0;
	str = malloc(sizeof(char));
	str[0] = '\0';
	j = 0;
	// if (lst && (lst->av_quotes))
	// 	return (line);
	// printf("line = %s\n", line);
	while (line[x])
	{
		if (line[x] == '$')
		{
			x++;
			j = x;
			while (line[j] && ((line[j] >= 'a' && line[j] <= 'z')
				|| (line[j] >= 'A' && line[j] <= 'Z')
				|| (line[j] >= '0' && line[j] <= '9')))
			{
					j++;
			}
			to_expand = ft_substr(line, x, j - 1);
			while (env_parse)
			{
				i = 0;
				env_split = NULL;
				env_split = malloc(sizeof(char));
				env_split[0] = '\0';
				while (env_parse->value && env_parse->value[i] != '=')
				{
					env_split = ft_chrjoin(env_split, env_parse->value[i]);
					i++;
				}
				if (!(ft_strcmp(to_expand, env_split)))
				{
					str = ft_substr(env_parse->value, i + 1,
						ft_strlen(env_parse->value));
				}
				free (env_split);
				env_parse = env_parse->next;
			}
			x = j - 1;
		}
		else
			str = ft_chrjoin(str, line[x]);
		x++;
	}
	return (str);
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
   	pipe(fd);
	args->infile = fd[0];
	args->outfile = 1;
	id = fork();
	signal(SIGINT, SIG_IGN);
	if (id == 0)
	{
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
				str = heredoc_expand(line, env_parse, lst);
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
