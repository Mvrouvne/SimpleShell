/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:56 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/27 23:31:24 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*expand(char *line, int *x, t_env *env_parse)
{
	char	*to_expand;
	char	*expanded = NULL;
	int		y;
	int		z;
	int		j;
	char 	*str;
	z = 0;
	y = 0;
	str = malloc(sizeof(char));
	str[0] = '\0';
	(*x)++;
	y = *x;
	j = 0;
	while (line[y] && ((line[y] >= 'a' && line[y] <= 'z')
		|| (line[y] >= 'A' && line[y] <= 'Z')
		|| (line[y] >= '0' && line[y] <= '9')))
	{
		y++;
		j++;
	}
	to_expand = ft_substr(line, *x, j);
	while (env_parse)
	{
		if (!(ft_strncmp(to_expand, env_parse->value, ft_strlen(to_expand))))
		{
			expanded = ft_substr(env_parse->value, ft_strlen(to_expand) + 1,
				ft_strlen(env_parse->value));
			break ;
		}
		env_parse = env_parse->next;
	}
	*x = y;
	return (expanded);
}
