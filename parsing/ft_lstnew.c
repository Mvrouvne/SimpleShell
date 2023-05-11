/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:37:23 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/11 22:53:32 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_lstnew(char *data)
{
	t_token	*head;

	head = NULL;
	head = malloc(sizeof(void));
	head->data = data;
	head->next = NULL;
	return (head);
}
	