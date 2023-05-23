/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:12:21 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/23 16:43:47 by otitebah         ###   ########.fr       */
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

char	*ft_strcpy(char *dest, char *src);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_strcmp_o(const char *s1, const char *s2);

t_list	*create_node(char *value);
int		check_plus(char **p, t_list *saving_expo);
int		cd(char **p, t_list *saving_expo);

t_list	*get_env(char **env);

t_list	*export(char *p, t_list **saving_expo);
void	execution(t_args **p, t_list **saving_env, t_list **saving_expo,char **env);
void    export_a(t_list **saving_expo, t_list **saving_env, t_args **p);

t_list	*sort_list(t_list **saving_expo);
t_list	*search_node(t_list *saving_env, char *node);
int		search_home(t_list *saving_expo, char *node);
char	*search_path(t_list *saving_expo, char *node);
int		search_plus(char *str);
int		search_egal(char *str);

void	Implement_Cmnd(t_list *saving_expo, t_args *p, char **env);
void	big_cd(t_list **saving_env, t_list **saving_expo, t_args **p);
void	modify_Pwd(t_list **saving_env, char *new_pwd);
void	add_OldPwd(t_list **saving_env, char *old_pwd);

t_data g_data;

#endif