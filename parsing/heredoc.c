/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:59:57 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/26 23:16:29 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*heredoc_expand(char *line, t_env *env_parse)
{
	char	*to_expand;
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
					puts("HHH");
					j++;
			}
			to_expand = ft_substr(line, x, j);
			printf("to_expand = %s\n", to_expand);
			while (env_parse)
			{
				if (!(ft_strncmp(to_expand, env_parse->value, ft_strlen(to_expand))))
				{
					str = ft_strjoin(str, ft_substr(env_parse->value, ft_strlen(to_expand) + 1,
						ft_strlen(env_parse->value)));
				}
				env_parse = env_parse->next;
			}
		}
		else
			str = ft_chrjoin(str, line[x]);
		x++;
	}
	// while (line[x] && ((line[x] >= 'a' && line[x] <= 'z')
	// 	|| (line[x] >= 'A' && line[x] <= 'Z')
	// 	|| (line[x] >= '0' && line[x] <= '9')))
	// {
	// 	x++;
	// 	j++;
	// }
	// x = 0;
	// to_expand = ft_substr(line, x, j);
	// printf("to_expand = %s\n", to_expand);
	// while (env_parse)
	// {
	// 	if (!(ft_strncmp(to_expand, env_parse->value, ft_strlen(to_expand))))
	// 	{
	// 		line = ft_substr(env_parse->value, ft_strlen(to_expand) + 1,
	// 			ft_strlen(env_parse->value));
	// 		y++;
	// 		break ;
	// 	}
	// 	env_parse = env_parse->next;
	// }
	return (str);
}

int	heredoc(t_args *args, char *delimiter, t_env *env_parse)
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
	args->infile = fd[0];
	args->outfile = 1;
    while (1)
    {
        write(1, "> ", 2);
	    line = get_next_line(0);
        if (!line || (!(ft_strncmp(line, delimiter, ft_strlen(line) - 1))))
        {
            free (line);
            return (1);
        }
		// printf("line = %s\n", line);
        str = heredoc_expand(line, env_parse);
		// printf("str = %s\n", str);
        write(fd[1], str, ft_strlen(line));
        free (line);
    }
    return (0);
}
