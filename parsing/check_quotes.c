/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:31 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/16 20:07:34 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_quotes(t_token **lst, char *line, int *x)
{
	int		holder;
	char 	*str;
	int		y;

	y = 0;
	holder = *x;
	while (line[*x])
	{
		if (line[*x] == '"')
		{
			(*x)++;
			y = *x;
			while (line[*x] != '"')
			{
				y++;
				(*x)++;
			}
			*x = y;
			str = malloc(sizeof(char) * (y + 1));
			y = 0;
			while (line[*x] != '"')
			{
				str[y] = line[*x];
				y++;
				(*x)++;
			}
			str[y] = '\0';
			if (line[*x] != '"')
				ft_lstadd_back(lst, ft_lstnew(str));
			else
				break ;
			// free (str);
		}
		else if (line[*x] == '\'')
		{
			(*x)++;
			y = *x;
			while (line[*x] != '\'')
			{
				y++;
				(*x)++;
			}
			*x = y;
			str = malloc(sizeof(char) * (y + 1));
			y = 0;
			while (line[*x] != '\'')
			{
				str[y] = line[*x];
				y++;
				(*x)++;
			}
			str[y] = '\0';
			if (line[*x] != '\'')
				ft_lstadd_back(lst, ft_lstnew(str));
			else
				break ;
			// free (str);
		}
		(*x)++;
	}
	return (0);
}