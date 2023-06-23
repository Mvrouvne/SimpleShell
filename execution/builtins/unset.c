/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:51:02 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/23 02:56:29 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	norm(t_list **head, t_list *cur)
{
	(*head) = cur->next;
	free(cur);
}

void	unset(t_list **head, char *key)
{
	t_list	*cur;
	t_list	*prev;
	char	*join;

	cur = (*head);
	prev = NULL;
	join = ft_strjoin(key, "=");
	while ((cur && cur->next != NULL) && (ft_strncmp(cur->value, join,
				ft_strlen(join)) || search_egal(cur->value) == 0))
	{
		prev = cur;
		cur = cur->next;
	}
	if (prev == NULL && cur)
		norm(head, cur);
	else if (cur && prev && (ft_strncmp(cur->value, join, ft_strlen(join)) == 0
			|| search_egal(cur->value) == 0))
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
