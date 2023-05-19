/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:31 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/19 16:41:24 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_quotes(t_token **lst, char *line, int *x, char *str2)
{
	char *str;
	int	d_quote;
	int	s_quote;
	int	d_count;
	int	s_count;
	int	temp;

	d_count = 0;
	s_count = 0;
	if (!str2)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	else
	{
		str = malloc(sizeof(char) * ft_strlen(str) + 1);
		str = str2;
	}
	// str[0] = '\0';
	d_quote = 0;
	s_quote = 0;
	temp = *x;
	while(line[*x])
	{
		if (line[*x] == '"')
			d_count++;
		else if (line[*x] == '\'')
			s_count++;
		(*x)++;
	}
	*x = temp;
	while (line[*x])
	{
		if (line[*x] == '"')
		{
			(*x)++;
			while (line[*x] != '"')
			{
				str = ft_chrjoin(str, line[*x]);
				(*x)++;
			}
		}
		else if (line[*x] == '\'')
		{
			(*x)++;
			while (line[*x] != '\'')
			{
				str = ft_chrjoin(str, line[*x]);
				(*x)++;
			}
		}
		else 
			str = ft_chrjoin(str, line[*x]);
		(*x)++;
	}
	if (str)
	{
		// if (count % 2 != 0)
		// {
		// 	write(2, "quote not closed!\n", 19);
		// 	exit (1);
		// }
		ft_lstadd_back(lst, ft_lstnew(str));
	}
	return (0);
}
