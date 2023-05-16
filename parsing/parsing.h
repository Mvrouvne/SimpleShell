/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:25 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/16 22:35:08 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef	PARSING_H
# define	PARSING_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5

# endif

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
// # include "../minishell.h"

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
// size_t	ft_strlen(const char *str);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
t_args	*ft_lstlast2(t_args *lst);
int		create_list(t_args **args, t_token *token);
int		args_count(t_token *lst);
void	check_in_out(t_args *args, int in, int out);
int		heredoc(char *delimiter);
char	*get_next_line(int fd);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_strchr(char *str, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		check_quotes(t_token **lst, char *line, int *x);
int	lexing(char *line, t_token **lst, int *x);
int	lexing2(char *line, t_token **lst, int *x);
int	lexing3(char *line, t_token **lst, int *x);
int	lexing4(t_token	**lst);
int	split_args(t_token **lst, t_args **args);

# endif