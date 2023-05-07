/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:37:23 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/07 11:14:14 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew(char *data)
{
	t_token	*head;

	head = NULL;
	head = malloc(sizeof(t_token));
	head->data = data;
	head->next = NULL;
	return (head);
}
	