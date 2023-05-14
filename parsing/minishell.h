/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:25 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/14 19:04:44 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef	MINISHELL_H
# define	MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_definitions
{
	CMD = 0,
	INPUT = 1,
	OUTPUT = 2,
	L_OP = 3,
	R_OP = 4,
	APPEND = 5,
	HEREDOC = 6,
	PIPE = 7,
	ARG = 8,
	DELIMITER = 9,
};

typedef struct  s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
}   t_token;

typedef struct s_args
{
    char	**args;
    int		infile;
    int		outfile;
    struct s_args *next;
}   t_args;

void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstadd_back2(t_args **lst, t_args *new);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew(char *data);
t_args	*ft_lstnew2(void);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
t_args	*ft_lstlast2(t_args *lst);
int		create_list(t_args **args, t_token *token);
int		args_count(t_token *lst);
void	check_in_out(t_args *args, int in, int out);
int		heredoc(char *delimiter);
char	*get_next_line(int fd);

# endif