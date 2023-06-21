/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:13:57 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/21 12:23:26 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list	*search_node(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node))) == 0)
		{
            puts("node");
			printf("tmp :%s\n", tmp->value);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_list	*search_node1(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node) - 1)) == 0)
		{
            puts("node");
			printf("tmp :%s\n", tmp->value);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int search_node_1(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node) - 1)) == 0)
		{
            puts("node");
			printf("tmp :%s\n", tmp->value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void    export_a(t_list **saving_env, t_list **saving_expo, t_args *p)
{
    int     x;
    int     i;
    char    **spl_p;
    
    x = 0;
    i = 1;
    if (p->args[i])
    {
        while (p->args[i])
        {
            if (error_export(p->args, i) == 0)
                return ;
            else if (search_plus(p->args[i]) == 0 && search_egal(p->args[i]) == 0
                    && !search_node(*saving_expo, p->args[i]))
                (*saving_expo) = export(p->args[i], &(*saving_expo));
            else if (search_egal(p->args[i]) == 3)
            {
                (*saving_env) = export(p->args[i], &(*saving_env));
                (*saving_expo) = export(p->args[i], &(*saving_expo));
            }
            else if (search_egal(p->args[i]) == 1 && search_plus(p->args[i]) == 0)
                equal_no_plus(saving_expo, saving_env, p->args[i]);
            else if (search_plus(p->args[i]) == 2)
            {
                    spl_p = ft_split(p->args[i], '+');
                    if(if_plus(saving_expo, saving_env, p->args[i]) == 1);
                    else if (search_node(*saving_expo, spl_p[0]))
                    {
                        if_plus2(saving_expo, saving_env, p->args[i]);
                        if_plus3(saving_expo, saving_env, p->args[i]);
                    }
            }
            i++;
        }
    }
    else
    {
        if (*saving_expo)
            print_export(saving_expo);
    }
}

void    ft_error(char *entourage, char *input, char *error, int i)
{
    ft_putstr_fd(entourage, i);
    ft_putstr_fd(input, i);
    ft_putstr_fd(": ", i);
    ft_putendl_fd(error, i);
}

void	ft_free(char **str)
{
	int		i;

	i = 0;
    if (!str)
        return ;
	while (str[i])
		free(str[i++]);
	free(str);
}