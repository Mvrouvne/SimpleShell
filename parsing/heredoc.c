/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:59:57 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/14 23:04:56 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *delimiter)
{
    char    *line;
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
            break ;
        write(fd[1], line, ft_strlen(line));
        free (line);
    }
    return (0);
}
