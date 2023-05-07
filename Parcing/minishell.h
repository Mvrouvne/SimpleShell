/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:25 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/07 16:17:39 by machaiba         ###   ########.fr       */
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

enum e_definitions
{
	CMD = 0,
	INPUT = 1,
	OUTPUT = 3,
	L_OP = 4,
	R_OP = 5,
	APPEND = 6,
	HERDOC = 7,
	PIPE = 8,
};

typedef struct  s_token
{
	int				type;
	char*			data;
	struct s_token	*next;
}   t_token;

// typedef struct s_data
// {
//     char **args;
//     int in_file;
//     int outfile;
//     struct s_data *next;
// }   t_data;

void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew(char *data);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

# endif