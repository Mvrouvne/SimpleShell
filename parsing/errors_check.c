/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:32:35 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/24 16:29:25 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	errors_check(t_token *lst)
{
	int	x;

	x = 0;
	while (lst)
	{
		if ((!(lst->next)) && ((!(ft_strcmp(lst->data, "<"))) || (!(ft_strcmp(lst->data, "<<")))
			|| (!(ft_strcmp(lst->data, ">")) || (!(ft_strcmp(lst->data, ">>"))))))
		{
			write (2, "syntax error near unexpected token `newline'\n", 46);
			return (1);
		}
		else if ((lst->next) && ((!(ft_strcmp(lst->data, "<"))) || (!(ft_strcmp(lst->data, "<<")))
			|| (!(ft_strcmp(lst->data, ">")) || (!(ft_strcmp(lst->data, ">>"))))))
		{
			if (!(ft_strcmp(lst->next->data, "|")))
			{
				write (2, "syntax error near unexpected token `|'\n", 40);
				return (1);
			}
		}
		lst = lst->next;
	}
	return (0);
}
