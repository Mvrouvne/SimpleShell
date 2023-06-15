/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 10:22:04 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/15 21:39:56 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../execution.h"

int	check_n(char *str)
{
	int	i;

	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (2);
}

void	echo(char **p, t_args *out)
{
		int	i;

	i = 1;
	if (p[i] == NULL)
	{
		ft_putstr_fd("\n", out->outfile);
		return ;
	}
	while (p[i])
	{
		if (check_n(p[i]) == 1)
		{
			while (p[i])
			{
				ft_putstr_fd(p[i++],  out->outfile);
				if (p[i])
					ft_putstr_fd(" ",  out->outfile);
			}
			if (check_n(p[1]) == 1 || check_n(p[1]) == 2)
				ft_putstr_fd("\n",  out->outfile);
			return ;
		}
		else if (check_n(p[i]) == 2)
		{
			while (p[i])
			{
				ft_putstr_fd(p[i++],  out->outfile);
				if (p[i])
					ft_putstr_fd(" ",  out->outfile);
			}
			if (check_n(p[1]) == 1 || check_n(p[1]) == 2)
				ft_putstr_fd("\n",  out->outfile);
			return;
		}
		i++;
	}
}

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

void	builtins(t_args *p, t_list **saving_env, t_list **saving_expo)
{
	int		i;
	t_list	*tmp;
	t_list	*new;

	if (!p->args[0])
		return ;
	if (!ft_strcmp(p->args[0], "echo"))
		echo(p->args, p);
	else if (!ft_strcmp(p->args[0], "pwd"))
	{
		char filename[256];
		getcwd(filename, 256);
		ft_putendl_fd(filename, p->outfile);
	}
	else if (!ft_strcmp(p->args[0], "cd"))
		big_cd(saving_env, saving_expo, p);
	else if (!ft_strcmp(p->args[0], "env"))
	{
		i = 1;
		while(p->args[i])
		{
			if (search_egal(p->args[i]) == 1)
			{
				new = create_node(p->args[i]);
				ft_lstadd_front(saving_env, new);
			}
			else if (p->args[i])
			{
				ft_putstr_fd("env: ", 1);
				ft_putstr_fd(p->args[i], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
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
	else if (!ft_strcmp(p->args[0], "unset"))
	{
		i = 1;
		while (p->args[i])
		{
			unset(saving_expo, p->args[i]);
			unset(saving_env, p->args[i]);
			i++;
		}
	}
	else if (!ft_strcmp(p->args[0], "export"))
		export_a(saving_expo, saving_env, p);
	else if (!ft_strcmp(p->args[0], "exit"))
	{
		i = 1;
		if (p->args[i])
		{
			int return_value;
			return_value = ft_atoi(p->args[i]);
			exit(return_value);
		}
		else
			exit (0);
	}
}

// void ft_error(char *msg, char *str)
// {
// 	ft_putstr_fd(msg, 2);
// 	ft_putendl_fd(str, 2);
// }