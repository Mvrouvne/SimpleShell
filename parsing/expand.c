/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:56 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/19 23:32:27 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*expand(t_token *lst, char *line, int *x, t_env *env_parse)
{
	char	*to_expand;
	char	*expanded = NULL;
	int		y;
	int		check1;
	int		check2;
	int		j;
	int		i;
	char 	*str;
	char 	*env_split;
	extern int	g_exit_status;

	check1 = 0;
	check2 = 0;
	y = 0;
	i = 0;
	while (lst)
	{
		if ((!(ft_strcmp(lst->data, ">")) || (!(ft_strcmp(lst->data, ">>"))
			|| (!(ft_strcmp(lst->data, "<"))))))
		{
			check1++;
			break ;
		}
		lst = lst->next;
	}
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
		i = 0;
		env_split = NULL;
		env_split = malloc(sizeof(char));
		env_split[0] = '\0';
		while (env_parse->value && env_parse->value[i] != '=')
		{
			env_split = ft_chrjoin(env_split, env_parse->value[i]);
			i++;
		}
		if (!(ft_strcmp(to_expand, env_split)))
		{
			expanded = ft_substr(env_parse->value, i + 1,
				ft_strlen(env_parse->value));
			check2++;
		}
		free (env_split);
		env_parse = env_parse->next;
	}
	if ((check1 && !check2))
	{
		puts("HEEREE");
		write (2, "$", 1);
		write (2, to_expand, ft_strlen(to_expand));
		write (2, ": ambiguous redirect\n", 22);
		free (to_expand);
		free (str);
		g_exit_status = 1;
		return (NULL);
	}
	*x = y;
	free (to_expand);
	free (str);
	return (expanded);
}
