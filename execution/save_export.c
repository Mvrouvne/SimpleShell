/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:12:53 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/16 07:34:20 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
            // break ;
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
	// int i = 0;   //////
	(void)node;
	tmp = saving_expo;
    // printf("am here\n");
    // while(tmp)
    // {
    //     printf("tmp :%s\n", tmp->value);
    //     tmp = tmp->next;
    // }
    // exit(1);
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

// int	check_plus(char **p, t_list *saving_expo)
// {
// 	int		i;
// 	int		x;
// 	char	**spl;
// 	t_list	*tmp;

// 	i = 0;
// 	tmp = saving_expo;
// 	while (saving_expo->next != NULL)
// 	{
// 		while (p[i])
// 		{
// 			spl = ft_split(p[i], '=');
// 			// printf("%s\n", spl[0]);
// 			// i = ft_strlen(spl[0]) - 1;
// 			// printf("%d\n", i);
// 			// exit (0);
// 			printf("%s\n", spl[0]);
// 			printf("%s\n", saving_expo->value);
// 			if (!ft_strncmp(spl[0], saving_expo->value, (ft_strlen(spl[0]) - 1)))
// 			{
// 				puts("samaykom");
// 				x = 0;
// 				while (p[i][x])
// 				{
// 					if (p[i][x] == '+')
// 						return (0) ;
// 					x++;
// 				}
// 			}
// 			i++;
// 		}
// 		saving_expo = saving_expo->next;
// 	}
// 	return (1);
// }