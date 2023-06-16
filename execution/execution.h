/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:12:21 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/16 16:40:28 by otitebah         ###   ########.fr       */
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
    char    *value;
    struct s_list *next;
    t_args  *args;
}   t_list;

typedef struct s_pipe {
    int     cmds;
    int		fd[2];
    int     tmp;
}   t_pipe;

typedef struct  s_data
{
    t_list *saving_expo;
    t_list *saving_env;
    t_args *p;
}   t_data;


void   add_node(t_list **head, t_list *new_node);
void	add_OldPwd(t_list **saving_env, char *old_pwd);

void	big_cd(t_list **saving_env, t_list **saving_expo, t_args *p);

int		ft_strcmp_o(const char *s1, const char *s2);
void	ft_lstadd_front(t_list **lst, t_list *new);
char	*ft_strcpy(char *dest, char *src);
t_args	*ft_lstnew4(char *data);
void    ft_error(char *entourage, char *input, char *error, int i);
void	ft_lstadd_back3(t_list **lst, t_list *new);

int		check_plus(char **p, t_list *saving_expo);
int     check_if_builtins(t_args *p);
int		cd(char **p, t_list *saving_expo);
t_list	*create_node(char *value);
void	check_slash(t_args *p, char **env);
void	child_exec_solo_cmd(t_args *p, t_list *saving_expo, char **env_copy);

t_list	*get_env(char **env);
t_list	*get_expo(char **env);

void	echo(char **p, t_args *out);
void	builtins(t_args *p, t_list **saving_env, t_list **saving_expo);
int     execute_cmd(t_args *p, t_list *saving_expo, char **env_copy);
int     execute_cmd_pipe(t_args *p, t_list *saving_expo, char **env);
void    export_a(t_list **saving_env, t_list **saving_expo, t_args *p);
void    *env_if_egal(char *p, t_list **saving_env);
t_list	*export(char *p, t_list **saving_expo);
t_list	*env_i(t_list **saving_env);

char	*search_path(t_list *saving_expo, char *node);
t_list	*search_node(t_list *saving_env, char *node);
int		search_home(t_list *saving_expo, char *node);
t_list	*search_oldpwd(t_list *saving_env);
t_list	*sort_list(t_list **saving_expo);
t_list	*search_pwd(t_list *saving_env);
int		search_plus(char *str);
int		search_egal(char *str);

void	Implement_Cmnd(t_data *lst, t_args *p, char **env, t_pipe *pipe);

void	unset(t_list **head, char *key);

void	modify_Pwd(t_list **saving_env, char *new_pwd);

t_data g_data;

#endif