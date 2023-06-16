/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 10:22:04 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/16 16:49:35 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../execution.h"

void	unset(t_list **head, char *key)
{
	t_list	*cur;
	t_list	*prev;

	cur = (*head);
	prev = NULL;
	while(cur && cur->next != NULL && ft_strncmp(cur->value, key, ft_strlen(key)))
	{
		prev = cur;
		cur = cur->next;
	}
	if (prev == NULL && cur )
		(*head) = cur->next;
	else if (cur && prev && ft_strncmp(cur->value, key, ft_strlen(key)) == 0)
		prev->next = cur->next;
}

void	env(t_args *p, t_list **saving_env, int i)
{
	puts("im here");
	t_list	*tmp;

	i = 1;
	while(p->args[i])
	{
		if (p->args[i])
		{
			ft_error("env: ", p->args[i], "No such file or directory", 1);
			return ;
		}
		i++;
	}
	tmp = (*saving_env);
	while (*saving_env)
	{
		ft_putendl_fd((*saving_env)->value, p->outfile);
		*saving_env = (*saving_env)->next;
	}
	(*saving_env) = tmp;
}

int	builtins_utils(t_args *p, t_list **saving_env, t_list **saving_expo)
{
	if (!ft_strcmp(p->args[0], "echo"))
	{
		echo(p->args, p);
		return (1);
	}
	else if (!ft_strcmp(p->args[0], "pwd"))
	{
		char filename[256];
		getcwd(filename, 256);
		ft_putendl_fd(filename, p->outfile);
		return (1);
	}
	else if (!ft_strcmp(p->args[0], "cd"))
	{
		big_cd(saving_env, saving_expo, p);
		return (1);
	}
	return (0);
}


void	builtins(t_args *p, t_list **saving_env, t_list **saving_expo)
{
	int		i;

	extern int exit_status;
	i = 1;
	if (!p->args[0])
		return ;
	else if(builtins_utils(p, saving_env, saving_expo) == 1);
	else if (!ft_strcmp(p->args[0], "env"))
		env(p, saving_env, i);
	else if (!ft_strcmp(p->args[0], "unset"))
	{
		while (p->args[i])
		{
			unset(saving_expo, p->args[i]);
			unset(saving_env, p->args[i]);
			i++;
		}
	}
	else if (!ft_strcmp(p->args[0], "export"))
		export_a(saving_env, saving_expo, p);
	else if (!ft_strcmp(p->args[0], "exit"))
		exit (exit_status);
}