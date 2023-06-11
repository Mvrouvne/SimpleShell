/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 10:22:04 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/11 15:54:11 by otitebah         ###   ########.fr       */
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

void	echo(char **p)
{
		int	i;

	i = 1;
	if (p[i] == NULL)
	{
		printf("\n");
		return ;
	}
	while (p[i])
	{
		if (check_n(p[i]) == 1)
		{
			while (p[i])
			{
				printf("%s", p[i++]);
				if (p[i])
					printf(" ");
			}
			if (check_n(p[1]) == 1 || check_n(p[1]) == 2)
				printf("\n");
			return ;
		}
		else if (check_n(p[i]) == 2)
		{
			while (p[i])
			{
				printf("%s", p[i++]);
				if (p[i])
					printf(" ");
			}
			if (check_n(p[1]) == 1 || check_n(p[1]) == 2)
				printf("\n");
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

int	echo_pwd_cd(t_args **p, t_list** saving_env, t_list **saving_expo)
{
	t_list	*tmp;

	if (!ft_strcmp((*p)->args[0], "echo"))
	{
		echo((*p)->args);
		return (1);
	}
	else if (!ft_strcmp((*p)->args[0], "pwd"))
	{
		char filename[256];
		getcwd(filename, 256);
		printf("%s\n", filename);
		return (1);
	}
	else if (!ft_strcmp((*p)->args[0], "cd"))
	{
		big_cd(&(*saving_env), &(*saving_expo), p);
		return (1);
	}
	else if (!ft_strcmp((*p)->args[0], "env"))
	{
		tmp = (*saving_env);
		while (*saving_env)
		{
			printf("%s\n", (*saving_env)->value);
			(*saving_env) = (*saving_env)->next;
		}
		(*saving_env) = tmp;
		return (1);
	}
	return (0);
}

void	execution(t_args **p, t_list **saving_env, t_list **saving_expo, char **env, t_pipe *pipes)
{
	int		i;

	if (!(*p)->args[0])
		return ;
	else if (echo_pwd_cd(p, saving_env, saving_expo) == 1);
	else if (!ft_strcmp((*p)->args[0], "unset"))
	{
		i = 1;
		while ((*p)->args[i])
		{
			unset(saving_expo, (*p)->args[i]);
			unset(saving_env, (*p)->args[i]);
			i++;
		}
	}
	else if (!ft_strcmp((*p)->args[0], "exit"))
	{
		i = 1;
		if ((*p)->args[i])
		{
			int return_value;
			return_value = ft_atoi((*p)->args[i]);
			exit(return_value);
		}
		else
			exit (0);
	}
	else if (!ft_strcmp((*p)->args[0], "export"))
		export_a(saving_expo, saving_env, p);
	else	
		Implement_Cmnd((*saving_expo), *p, env, pipes);
}
