/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:31 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/18 13:06:46 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_quotes(t_token **lst, char *line, int *x)
{
	char *str;
	int	d_quote;
	int	s_quote;

	str = malloc (sizeof(char));
	str[0] = '\0';
	d_quote = 0;
	s_quote = 0;
	while (line[*x])
	{
		if (line[*x] == '"')
		{
			if (s_quote == 1)
				str = ft_chrjoin(str, line[*x]);
			d_quote++;
		}
		else if (line[*x] == '\'')
		{
			if (d_quote == 1)
				str = ft_chrjoin(str, line[*x]);
			s_quote++;
		}
		else
			str = ft_chrjoin(str, line[*x]);
		(*x)++;
	}
	if (str)
		ft_lstadd_back(lst, ft_lstnew(str));
	return (0);
}
