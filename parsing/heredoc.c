/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:59:57 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/26 18:11:21 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*heredoc_expand(char *line, t_env *env_parse)
{
	char	*to_expand;
	char	*expanded = NULL;
    int     x;
	int		y;
	int		z;
	int		j;
	char 	*str;
    x = 0;
	z = 0;
	y = 0;
	str = malloc(sizeof(char));
	str[0] = '\0';
	j = 0;
	while (line[x] && ((line[x] >= 'a' && line[x] <= 'z')
		|| (line[x] >= 'A' && line[x] <= 'Z')
		|| (line[x] >= '0' && line[x] <= '9')))
	{
		x++;
		j++;
	}
	to_expand = ft_substr(line, x, j);
	while (env_parse)
	{
		if (!(ft_strncmp(to_expand, env_parse->value, ft_strlen(to_expand))))
		{
			expanded = ft_substr(env_parse->value, ft_strlen(to_expand) + 1,
				ft_strlen(env_parse->value));
			break ;
		}
		env_parse = env_parse->next;
	}
	return (expanded);
}

int	heredoc(char *delimiter, t_env *env_parse)
{
    char    *line;
    char    *str;
    int     fd[2];
    
    
    // fd = open("heredoc_file", O_CREAT | O_RDWR | O_APPEND, 0777);
    pipe(fd);
    // if (fd == -1)
    // {
    //     write(2, "heredoc file failed\n", 21);
    //     exit (1);
    // }
    while (1)
    {
        write(1, "> ", 2);
	    line = get_next_line(0);
        if (!line || (!(ft_strncmp(line, delimiter, ft_strlen(line) - 1))))
        {
            free (line);
            return (1);
        }
        str = heredoc_expand(line, env_parse);
        write(fd[1], str, ft_strlen(line));
        free (line);
    }
    return (0);
}
