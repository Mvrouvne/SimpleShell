/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:58:03 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/04 16:50:00 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


t_list	*search_OldPwd(t_list *saving_env)
{
	t_list	*tmp = NULL;
	
	tmp = saving_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "OLDPWD=", 7) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list	*search_Pwd(t_list *saving_env)
{
	t_list	*tmp = NULL;
	
	tmp = saving_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "PWD=", 4) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	modify_Pwd(t_list **saving_env, char *new_pwd)
{
	t_list	*pwd_found;
	
	pwd_found = search_Pwd(*saving_env);
	pwd_found->value = ft_strjoin("PWD=", new_pwd);
	
}

void	add_OldPwd(t_list **saving_env, char *old_pwd)
{
	t_list	*new = NULL;
	(void) saving_env;
	char	str[8] = "OLDPWD=";
	int		i;
	char	*new_str = NULL;
	t_list	*oldpwd_found = NULL;
	
	oldpwd_found = search_OldPwd(*saving_env);
	if (oldpwd_found != NULL)
		oldpwd_found->value = ft_strjoin("OLDPWD=", old_pwd);
	else
	{
		i = ft_strlen(old_pwd) + ft_strlen(str) + 1;
		new = (t_list *)malloc(sizeof(t_list));
		new_str = ft_strjoin(str, old_pwd);
		new->value = new_str;
		new->next = NULL;
		ft_lstadd_front(saving_env, new);
	}
}

int	cd(char **p, t_list *saving_expo)
{
	if (search_home(saving_expo, "HOME") == 0)
	{
		perror("minishell: cd");
		return (0);
	}
	else if (p[1] == NULL && search_home(saving_expo, "HOME") == 1)
	{
		puts("samaykom"); 
		chdir(getenv("HOME"));
	}
	else if ((!ft_strcmp(p[1], "~")) && search_home(saving_expo, "HOME") == 1)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else if (chdir(p[1]))
	{
		perror("minishell: cd");
		return (0);
	}
	return (1);
}

void	big_cd(t_list **saving_env, t_list **saving_expo, t_args **p)
{
	char old_pwd[256];
	char new_pwd[256];
	getcwd(old_pwd, 256);
	if (cd((*p)->args, (*saving_expo)) == 1)
	{
		getcwd(new_pwd, 256);
		add_OldPwd(saving_env, old_pwd);
		modify_Pwd(saving_env, new_pwd);
		add_OldPwd(saving_expo, old_pwd);
		modify_Pwd(saving_expo, new_pwd);
	}
}