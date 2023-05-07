/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:25 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/07 11:34:47 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef	MINISHELL_H
# define	MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ARG 2
# define INPUT 3
# define OUTPUT 4
# define TRUNC 5
# define APPEND 6
# define HERDOC 7
# define PIPE 8

typedef struct  s_token
{
    int  type;
    char            *data;
    struct s_token   *next;
}   t_token;

typedef struct s_data
{
    char **args;
    int in_file;
    int outfile;
    struct s_data *next;
}   t_data;

void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew(char *data);
size_t	ft_strlen(const char *str);

# endif