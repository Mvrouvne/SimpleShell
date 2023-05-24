/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:32:35 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/24 23:31:00 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	filenames_check(char *str)
{
	if ((!(ft_strcmp(str, "<"))) || (!(ft_strcmp(str, ">")))
		|| (!(ft_strcmp(str, "|"))) || (!(ft_strcmp(str, ";")))
		|| (!(ft_strcmp(str, "#"))))
		return (1);
	return (0);
}

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
			if (filenames_check(lst->next->data))
			{
				write (2, "syntax error near unexpected token `|'\n", 40);
				return (1);
			}
		}
		lst = lst->next;
	}
	return (0);
}
