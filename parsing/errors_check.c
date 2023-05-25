/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:32:35 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/25 22:43:37 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	filenames_check(char *str)
{
	if ((!(ft_strcmp(str, "<"))) || (!(ft_strcmp(str, ">")))
		|| (!(ft_strcmp(str, "<<"))) || (!(ft_strcmp(str, "<<")))
		|| (!(ft_strncmp(str, "|", 1))) || (!(ft_strcmp(str, ";")))
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
		if ((lst->next) && ((!(ft_strcmp(lst->data, "<"))) || (!(ft_strcmp(lst->data, "<<")))
			|| (!(ft_strcmp(lst->data, ">")) || (!(ft_strcmp(lst->data, ">>"))))))
		{
			if (filenames_check(lst->next->data))
			{
				write (2, "syntax error near unexpected token `", 37);
				write (2, lst->next->data, 2);
				// ft_putstr_fd(lst->next->data, 2);
				write (2, "\'\n", 2);
				return (1);
			}
		}
		lst = lst->next;
	}
	return (0);
}
