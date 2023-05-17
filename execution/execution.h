/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:12:21 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/17 12:55:20 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include "../minishell.h"
# include <stdlib.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
// # include "../parsing/parsing.h"
// # include "../minishell.h"

typedef struct s_list {
    char *value;
    struct s_list *next;
}   t_list;

typedef struct  s_data
{
   t_list *env;
   int exit_status;
}   t_data;

char    *ft_strcpy(char *dest, char *src);
t_list  *get_env(char **env);
void ft_lstadd_front(t_list **lst, t_list *new);
t_list  *sort_list(t_list **saving_expo);
t_list   *create_node(char *value);
t_list  *export(char *p, t_list **saving_expo);
int		check_plus(char **p, t_list *saving_expo);
t_list	*search_node(t_list *saving_env, char *node);
int     search_home(t_list *saving_expo, char *node);
char	*search_path(t_list *saving_expo, char *node);
void	execution(t_args *p, char **env);
int	ft_strcmp_o(const char *s1, const char *s2);

t_data g_data;

#endif