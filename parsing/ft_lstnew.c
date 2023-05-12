/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:37:23 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/12 21:40:43 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_args	*ft_lstnew3(void)
// {
// 	t_args	*head;

// 	head = NULL;
// 	head = malloc(sizeof(t_args));
// 	head->next = NULL;
// 	return (head);
// }

t_args	*ft_lstnew2(void)
{
	t_args	*head;

	head = NULL;
	head = malloc(sizeof(t_args));
	head->next = NULL;
	return (head);
}

t_token	*ft_lstnew(char *data)
{
	t_token	*head;

	head = NULL;
	head = malloc(sizeof(t_token));
	head->data = data;
	head->next = NULL;
	return (head);
}
