/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:28:56 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/21 20:06:26 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expanded_quotes(t_token **lst, char *str, char *line, int *x)
{
	(void) line;
	(void) *x;
	char	*expanded;
	int		y;

	expanded = malloc(sizeof(char));
	expanded[0] = '\0';
	y = 0;
	while (str[y])
	{
		if (str[y] == '"')
		{
			y++;
			while (str[y] != '"')
			{
				expanded = ft_chrjoin(expanded, str[y]);
				y++;
			}
		}
		else if (str[y] == '\'')
		{
			y++;
			while (str[y] != '\'')
			{
				expanded = ft_chrjoin(expanded, str[y]);
				y++;
			}
		}
		else 
			expanded = ft_chrjoin(expanded, str[y]);
		y++;
	}
	// *x = (*x) + y;
	// printf("*x = %d\n", *x);
	// while (line[*x] && line[*x] != ' ')
	// 	(*x)++;
	// printf("expanded = %s\n", expanded);
	// exit (0);
	// printf("line[*x]  = %c\n", line[*x] );
	if (expanded && (!line[*x] || line[*x] == ' '))
		ft_lstadd_back(lst, ft_lstnew(expanded));
	return (0);
}
