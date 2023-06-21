/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:17:49 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/21 18:02:05 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	error_export(char **str, int i)
{
	if ((str[i][0] < 'a' || str[i][0] > 'z') && (str[i][0] < 'A'
			|| str[i][0] > 'Z'))
	{
		ft_error("minishell: ", str[i], "not a valid identifier", 1);
		return (0);
	}
	return (1);
}

void	equal_no_plus(t_list **saving_expo, t_list **saving_env, char *str)
{
	t_list	*node;
	t_list	*node2;
	char	**spl_p;
	
	spl_p = ft_split(str, '=');
	node = search_node(*saving_expo, spl_p[0]);
	node2 = search_node(*saving_env, spl_p[0]);
	if (node)
	{
		puts("true");
		char *src;
		char *res;
		puts(spl_p[0]);
		puts(spl_p[1]);
		src = ft_strjoin(spl_p[0], "=");
		if (spl_p[1])
		{
			puts("spl_p[1]  mafihach null");
			res = ft_strjoin(src, spl_p[1]);
			free(node->value);
			node->value = ft_strdup(res);
			if (!node2)
				ft_lstadd_back3(saving_env, ft_lstnew3(res));
			else
			{
				free(node2->value);
				node2->value = ft_strdup(res);
			}
		}
	}
	 else
		(*saving_env) = export(str, &(*saving_env));
	(*saving_expo) = export(str, &(*saving_expo));
}

int	if_plus(t_list **saving_expo, t_list **saving_env, char *str)
{
	char    **spl;
	char    **spl_p;
	char **remove_plus;
	char *res;
	
	spl = ft_split(str, '=');
	spl_p = ft_split(str, '+');
	if(!search_node_1(*saving_expo, spl_p[0]))
	{
		puts("remove plus");
		remove_plus = ft_split(str, '+');
		res = ft_strjoin(remove_plus[0], remove_plus[1]);
		(*saving_expo) = export(res, &(*saving_expo));
		(*saving_env) = export(res, &(*saving_env));
		ft_free(remove_plus);
		free(res);
		return (1);
	}
	return (0);
}

void	if_plus2(t_list **saving_expo, t_list **saving_env, char *str)
{
	t_list	*node;
	t_list	*node2;
	char    **spl;
	char    **spl_p;
	char	*res;
	char	*final;
	char	*add_egal;
	char	**old_value;

	spl_p = ft_split(str, '+');
	spl = ft_split(str, '=');
	node = search_node(*saving_expo, spl_p[0]);
	node2 = search_node1(*saving_env, spl[0]);
	old_value = ft_split(node->value, '=');
	add_egal = ft_strjoin(old_value[0], "=");
	if (old_value[1])
	{
		puts("------");
		res = ft_strjoin(add_egal, old_value[1]);
		final = ft_strjoin(res, spl[1]);
	}
	else
	{
		puts("*****");
		res = ft_strjoin(node->value, "=");
		final = ft_strjoin(res, spl[1]);
	}
	// free(add_egal);
	// free(node->value);
	// ft_free(old_value);
	node->value = ft_strdup(final);
}

void	if_plus3(t_list **saving_env, char *str, char *spl_p)
{
	char    **spl;
	t_list	*node2;
	char *add_equal;
	char *res;
	char *final;
	char **old_value;

	spl = ft_split(str, '=');
	node2 = search_node1(*saving_env, spl[0]);
	if (search_node1(*saving_env, spl[0]))
	{
		puts("node2");
		old_value = ft_split(node2->value, '=');
		add_equal = ft_strjoin(&spl_p[0], "=");
		if (old_value[1])
		{
			puts("old\n");
			res = ft_strjoin(add_equal, old_value[1]);
			final = ft_strjoin(res, spl[1]);
		}
		else
			final = ft_strjoin(node2->value, spl[1]);
		node2->value = ft_strdup(final);
	}
}