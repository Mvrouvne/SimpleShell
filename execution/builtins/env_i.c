/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:40:48 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/16 15:47:20 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list	*ft_lstnew3(char *data)
{
	t_list	*head;

	head = NULL;
	head = malloc(sizeof(t_list));
	head->value = data;
	head->next = NULL;
	return (head);
}

t_list	*ft_lstlast3(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (0);
}
void	ft_lstadd_back3(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		ft_lstlast3(*lst)->next = new;
	}
}

t_list	*env_i(t_list **saving_env)
{
	char	*s1;
	char	*node;
	char	filename[256];
	// t_list	*head;
	s1 = "PWD=";
	getcwd(filename, 256);
	
	node = ft_strjoin(s1, filename);
	if (!*saving_env)
	{
		ft_lstadd_back3(saving_env, ft_lstnew3(node));
		ft_lstadd_back3(saving_env, ft_lstnew3("SHLVL=1"));
		ft_lstadd_back3(saving_env, ft_lstnew3("_=/usr/bin/env"));
	}
	return (*saving_env);
}