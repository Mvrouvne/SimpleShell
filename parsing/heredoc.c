/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:59:57 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/06 16:11:18 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*heredoc_expand(char *line, t_env *env_parse, t_token *lst)
{
	(void) lst;
	char	*to_expand;
    int     x;
	int		y;
	int		z;
	int		j;
	int		i;
	char 	*str;
    x = 0;
	z = 0;
	y = 0;
	i = 0;
	str = malloc(sizeof(char));
	str[0] = '\0';
	j = 0;
	if (lst && (lst->av_quotes))
		return (line);
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
			to_expand = ft_substr(line, x, j);
			while (env_parse)
			{
				i = 0;
				while (env_parse->value && env_parse->value[i] != '=')
					i++;
				if (!(ft_strncmp(to_expand, env_parse->value, i)))
				{
					str = ft_substr(env_parse->value, i + 1,
						ft_strlen(env_parse->value));
				}
				env_parse = env_parse->next;
			}
			x = j;
		}
		else
			str = ft_chrjoin(str, line[x]);
		x++;
	}
	return (str);
}

int	heredoc(t_args *args, char *delimiter, t_env *env_parse, t_token *lst)
{
    char    *line;
    char    *str;
    int     fd[2];
	int		x;
	int		check;
    
    x = 0;
	check = 0;
    // fd = open("heredoc_file", O_CREAT | O_RDWR | O_APPEND, 0777);
    pipe(fd);
    // if (fd == -1)
    // {
    //     write(2, "heredoc file failed\n", 21);
    //     exit (1);
    // }
	args->infile = fd[0];
	args->outfile = 1;
    while (1)
    {
        write(1, "> ", 2);
	    line = get_next_line(0);
        if (!line || (!(ft_strncmp(line, delimiter, ft_strlen(line) - 1))))
        {
            free (line);
			close (fd[1]);
            return (1);
        }
    	str = heredoc_expand(line, env_parse, lst);
		// printf("str = %s\n", str);
        write(fd[1], str, ft_strlen(str));
		write (fd[1], "\n", 1);
        free (line);
    }
    return (0);
}
