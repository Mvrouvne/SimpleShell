/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:12:53 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/16 20:14:23 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_list  *sort_list(t_list **saving_expo)
{
    t_list  *tmp;
    char *swap;

    tmp = (*saving_expo);
    while ((*saving_expo)->next != NULL)
    {
        if (ft_strncmp((*saving_expo)->value, (*saving_expo)->next->value, 1) > 0)
        {
            swap = (*saving_expo)->value;
            (*saving_expo)->value = (*saving_expo)->next->value;
            (*saving_expo)->next->value = swap;
            (*saving_expo) = tmp;
        }
        else
            (*saving_expo) = (*saving_expo)->next;
    }
    (*saving_expo) = tmp;
    return (*saving_expo);
}

t_list  *export(char *p, t_list **saving_expo)
{
    t_list  *new;
    t_list  *res;

    new = create_node(p);
    ft_lstadd_front(saving_expo, new);
    res = sort_list(saving_expo);
    return (res);
}

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

int search_home(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node) - 2)) == 0)
		{
			printf("tmp :%s\n", tmp->value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}


/// home ila makantch makhasch tkhdem dik cd 