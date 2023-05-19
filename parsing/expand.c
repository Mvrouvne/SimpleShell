/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:56 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/19 23:26:00 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expand(t_token **lst, char *line, int *x, t_env *env_parse)
{
	char	*to_expand;
	char	*expanded;
	int		y;

	*x += 3;
	y = *x;
	while (line[y] && line[y] != ' ')
		y++;
	to_expand = ft_substr(line, *x, y);
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
