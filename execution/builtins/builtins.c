/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 10:22:04 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/22 12:31:51 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	unset(t_list **head, char *key)
{
	t_list	*cur;
	t_list	*prev;
	char	*join;

	cur = (*head);
	prev = NULL;
	join = ft_strjoin(key, "=");
	while (cur && cur->next != NULL && ft_strncmp(cur->value, join,
			ft_strlen(join)))
	{
		prev = cur;
		cur = cur->next;
	}
	if (prev == NULL && cur)
	{
		(*head) = cur->next;
		free(cur);
	}
	else if (cur && prev && ft_strncmp(cur->value, join, ft_strlen(join)) == 0)
	{
		prev->next = cur->next;
		free(cur->value);
		free(cur);
	}
	free(join);
}

void	env(t_args *p, t_list **saving_env, int i)
{
	t_list	*tmp;

	tmp = NULL;
	i = 1;
	while (p->args[i])
	{
		if (p->args[i])
		{
			ft_error("env: ", p->args[i], "No such file or directory", 1);
			return ;
		}
		i++;
	}
	tmp = *saving_env;
	while (tmp)
	{
		ft_putendl_fd(tmp->value, p->outfile);
		tmp = tmp->next;
	}
}

int	builtins_utils(t_args *p, t_list **saving_env, t_list **saving_expo)
{
		char filename[256];

	if (!ft_strcmp(p->args[0], "echo"))
	{
		echo(p->args, p);
		return (1);
	}
	else if (!ft_strcmp(p->args[0], "pwd"))
	{
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

void	exit_func(char **str)
{
	extern int		g_exit_status;
	unsigned char	ex;

	if (str[1] && !str[2])
	{
		ex = ft_atoi(str[1]);
		exit(ex);
	}
	if (str[0] && str[1] && str[2])
	{
		ft_putstr_fd("minishell : exit: to many arguments\n", 1);
		g_exit_status = 1;
		return ;
	}
	else
		exit(g_exit_status);
}

void	builtins(t_args *p, t_list **saving_env, t_list **saving_expo)
{
	int			i;
	extern int	g_exit_status;

	g_exit_status = 0;
	i = 1;
	if (!p->args[0])
		return ;
	if (builtins_utils(p, saving_env, saving_expo) == 1)
		;
	else if (!ft_strcmp(p->args[0], "env"))
		env(p, saving_env, i);
	else if (!ft_strcmp(p->args[0], "unset"))
	{
		while (p->args[i])
		{
			if (search_home_unset(*saving_expo, p->args[i]))
				unset(saving_expo, p->args[i]);
			if (search_home_unset(*saving_env, p->args[i]))
				unset(saving_env, p->args[i]);
			i++;
		}
	}
	else if (!ft_strcmp(p->args[0], "export"))
		export_a(saving_env, saving_expo, p);
	else if (!ft_strcmp(p->args[0], "exit"))
		exit_func(p->args);
}
