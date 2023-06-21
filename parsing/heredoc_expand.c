/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:52:40 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/21 21:20:49 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*heredoc_expand2(t_env **env_parse, char *to_expand)
{
	char	*str = NULL;
	char	*env_split;
	int		i;

	i = 0;
	env_split = NULL;
	env_split = malloc(sizeof(char));
	env_split[0] = '\0';
	while ((*env_parse)->value && (*env_parse)->value[i] != '=')
	{
		env_split = ft_chrjoin(env_split, (*env_parse)->value[i]);
		i++;
	}
	if (!(ft_strcmp(to_expand, env_split)))
	{
		str = ft_substr((*env_parse)->value, i + 1,
			ft_strlen((*env_parse)->value));
	}
	free (env_split);
	(*env_parse) = (*env_parse)->next;
	return (str);
}

char	*heredoc_expand(char *line, t_env *env_parse, t_token *lst)
{
	(void) lst;
	char	*to_expand = NULL;
	int     x;
	int		y;
	int		z;
	int		j;
	int		i;
	char 	*str;
	char 	*str2;
	t_env *temp = NULL;

	str = NULL;
	x = 0;
	z = 0;
	y = 0;
	i = 0;
	// str = malloc(sizeof(char));
	// str[0] = '\0';
	j = 0;
	while (line[x])
	{
		if (line[x] == '$')
		{
			x++;
			j = x;
			while (line[j] && ((line[j] >= 'a' && line[j] <= 'z')
				|| (line[j] >= 'A' && line[j] <= 'Z')
				|| (line[j] >= '0' && line[j] <= '9')))
					j++;
			to_expand = ft_substr(line, x, j - 1);
			// printf("to_expand = [%s]\n", to_expand);
			temp = env_parse;
			while (env_parse)
			{
				str2 = heredoc_expand2(&env_parse, to_expand);
				if (str2)
					break ;
				// i = 0;
				// env_split = NULL;
				// env_split = malloc(sizeof(char));
				// env_split[0] = '\0';
				// while (env_parse->value && env_parse->value[i] != '=')
				// {
				// 	env_split = ft_chrjoin(env_split, env_parse->value[i]);
				// 	i++;
				// }
				// if (!(ft_strcmp(to_expand, env_split)))
				// {
				// 	str = ft_substr(env_parse->value, i + 1,
				// 		ft_strlen(env_parse->value));
				// }
				// free (env_split);
				// env_parse = env_parse->next;
			}
			env_parse = temp;
			x = j - 1;
			printf("str2 = %s\n", str2);
			if (str2)
				str = ft_strjoin(str, str2);
			free (str2);
		}
		else
			str = ft_chrjoin(str, line[x]);
		// printf("line[x] = %c\n", line[x]);
		x++;
	}
	free (to_expand);
	printf("str = %s\n", str);
	return (str);
}
