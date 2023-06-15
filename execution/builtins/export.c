/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:13:57 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/15 15:39:31 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list	*search_node(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node) - 2)) == 0)
		{
			printf("tmp :%s\n", tmp->value);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	search_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void    export_a(t_list **saving_expo, t_list **saving_env, t_args *p)
{
    t_list	*node;
    t_list	*node2;
	t_list	*tmp1;
    int     x;
    int     i;
    
    x = 0;
    i = 1;
    if (p->args[i])
    {
        while (p->args[i])
        {
            x = 0;
            while (p->args[i][x])
            {
                if(search_plus(p->args[i]) == 1)
                {
                    char **spl_p;
                    spl_p = ft_split(p->args[i], '=');
                    node = search_node((*saving_expo), spl_p[0]);
                    node2 = search_node((*saving_env), spl_p[0]);
                    if (node)
                    {	
                        char *res;
                        char *res1;
                        res = ft_strjoin(node->value, spl_p[1]);
                        res1 = ft_strjoin(node2->value, spl_p[1]);
                        node->value = res;
                        node2->value = res1;
                        return ;
                    }
                    else
                    {
                        char **Remove_Plus;
                        char *join;
                        Remove_Plus = ft_split(p->args[i], '+');
                        join = ft_strjoin(Remove_Plus[0], Remove_Plus[1]);
                        (*saving_env) = export(join, &(*saving_env));
                        return ;
                    }
                }
                else if (search_egal(p->args[i]) == 1 || search_egal(p->args[i]) == 2)
                {
                    if(search_egal(p->args[i]) == 2)
                    {
                        ft_putstr_fd("minishell: ", 1);
                        ft_putstr_fd(p->args[i], 1);
                        ft_putstr_fd(": not a valid identifier\n", 1);
                        return ;
                    }
                    env_if_egal(p->args[i], &(*saving_env));
                    (*saving_expo) = export(p->args[i], &(*saving_expo));
                    return ;
                }
                else
                {
                    (*saving_expo) = export(p->args[i], saving_expo);
                    return ;
                }
                x++;
            }
            i++;
        }
    }
    else
    {
        if (*saving_expo)
        {
            (*saving_expo) = sort_list(saving_expo);
            tmp1 = (*saving_expo);
            while ((*saving_expo))
            {
                printf("declare -x  %s\n", (*saving_expo)->value);
                (*saving_expo) = (*saving_expo)->next;
            }
            (*saving_expo) = tmp1;
        }
    }
}