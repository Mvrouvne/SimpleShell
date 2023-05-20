/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:56 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/20 17:01:31 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expand(t_token **lst, char *line, int *x, t_env *env_parse)
{
	char	*to_expand;
	char	*expanded;
	int		y;

	(*x)++;
	// while (line[*x] == '"')
	// 	(*x)++;
	if (line[*x - 1] == '"')
	{
		(*x)++;
	}
	y = *x;
	int j = 0;
	while (line[y] && line[y] != ' ' && line[y] != '"' && line[y] != '\'')
	{
		y++;
		j++;
	}
	to_expand = ft_substr(line, *x, j);
	// if (z)
	// {
		while (line[y] && (line[y] == '"' || line[y] == '\''))
			y++;
	// }
	*x = y;
	while (env_parse)
	{
		if (!(ft_strncmp(to_expand, env_parse->value, ft_strlen(to_expand))))
		{
			expanded = ft_substr(env_parse->value, ft_strlen(to_expand) + 1, ft_strlen(env_parse->value));
			if (expanded)
				ft_lstadd_back(lst, ft_lstnew(expanded));
			break ;
		}
		env_parse = env_parse->next;
	}
	return (0);
}
