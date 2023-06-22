/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:51:02 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/22 16:54:47 by otitebah         ###   ########.fr       */
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

void	unset_util(t_list **saving_env, t_list **saving_expo, char *str)
{
	if (search_home_unset(*saving_expo, str))
		unset(saving_expo, str);
	if (search_home_unset(*saving_env, str))
		unset(saving_env, str);
}
