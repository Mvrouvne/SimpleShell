/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:56 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/21 00:27:15 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expand(t_token **lst, char *line, int *x, t_env *env_parse)
{
	char	*to_expand;
	char	*expanded;
	int		y;
	int		z;
	int		j;
	char 	*str;
	char 	*str2;

	z = 0;
	y = 0;
	str = malloc(sizeof(char));
	str[0] = '\0';
	str2 = malloc(sizeof(char));
	str2[0] = '\0';
	while (line[*x] && (line[*x] == '"' || line[*x] == '\''))
	{
		str = ft_chrjoin(str, line[*x]);
		(*x)++;
	}
	(*x)++;
	y = *x;
	j = 0;
	while (line[y] && line[y] != ' ' && line[y] != '"' && line[y] != '\'')
	{
		y++;
		j++;
	}
	to_expand = ft_substr(line, *x, j);
	// printf("to_expand = %s\n", to_expand);
	while (env_parse)
	{
		if (!(ft_strncmp(to_expand, env_parse->value, ft_strlen(to_expand))))
		{
			expanded = ft_substr(env_parse->value, ft_strlen(to_expand) + 1, ft_strlen(env_parse->value));
			break ;
		}
		env_parse = env_parse->next;
	}
	str = ft_strjoin(str, expanded);
	*x = y;
	while (line[*x] && (line[*x] == '"' || line[*x] == '\''))
	{
		str = ft_chrjoin(str, line[*x]);
		(*x)++;
	}
	// printf("str = %s\n", str);
	expanded_quotes(lst, str, line, x);
	return (0);
}
