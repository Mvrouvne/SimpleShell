/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:56 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/22 16:17:03 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*expand(t_token **lst, char *line, int *x, t_env *env_parse)
{
	(void) lst;
	char	*to_expand;
	char	*expanded;
	int		y;
	int		z;
	int		j;
	char 	*str;
	// char 	*str2;

	z = 0;
	y = 0;
	str = malloc(sizeof(char));
	str[0] = '\0';
	if (line[*x] != '$')
	{
		z++;
		while (line[*x] && (line[*x] == '"' || line[*x] == '\''))
		{
			str = ft_chrjoin(str, line[*x]);
			(*x)++;
		}
	}
	(*x)++;
	y = *x;
	j = 0;
	while (line[y] && line[y] != ' ' && line[y] != '"'
		&& line[y] != '\'' && line[y] != '$')
	{
		y++;
		j++;
	}
	// printf("x = %d\n", *x);
	// printf("j = %d\n", j);
	to_expand = ft_substr(line, *x, j);
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
	// while (line[*x] && (line[*x] == '"' || line[*x] == '\''))
	// {
	// 	str = ft_chrjoin(str, line[*x]);
	// 	(*x)++;
	// }
	// printf("str = %s\n", str);
	// exit (0);
	// if (z)
	// 	expanded_quotes(lst, str, line, x);
	// else if (!line[*x] || line[*x] == ' ')
	// 	ft_lstadd_back(lst, ft_lstnew(str));
	return (str);
}
