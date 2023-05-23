/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:31 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/23 14:56:56 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_quotes(t_token **lst, char *line, int *x, t_env *env_parse)
{
	char	*str;
	char	*str2;
	// int	d_quote;
	// int	s_quote;
	int		d_count;
	int		s_count;
	int		y;
	int		temp;
	
	str = malloc(sizeof(char));
	str[0] = '\0';
	y = 0;
	d_count = 0;
	s_count = 0;
	temp = *x;
	while(line[temp])
	{
		if (line[temp] == '"')
			d_count++;
		else if (line[temp] == '\'')
			s_count++;
		temp++;
	}
	// if (d_count % 2 != 0 && d_count >= s_count)
	// {
	// 	write (2, "unclosed quote!\n", 17);
	// 	exit (1);
	// }
	// if (s_count % 2 != 0 && s_count >= d_count)
	// {
	// 	write (2, "unclosed quote!\n", 17);
	// 	exit (1);
	// }
	while (line[*x] && line[*x] != ' ')
	{
		if (line[*x] == '"')
		{
			(*x)++;
			while (line[*x] && line[*x] != '"')
			{
				if (line[*x] == '$')
				{
					str2 = expand(lst, line, x, env_parse);
					str = ft_strjoin(str, str2);
				}
				if (!(line[*x] == '"'))
					str = ft_chrjoin(str, line[*x]);
				(*x)++;
			}
		}
		else if (line[*x] == '\'')
		{
			(*x)++;
			while (line[*x] && line[*x] != '\'')
			{
				str = ft_chrjoin(str, line[*x]);
				(*x)++;
			}
		}
		else if (line[*x] == '$')
		{
			str2 = expand(lst, line, x, env_parse);
			if (str2)
				str = ft_strjoin(str, str2);
			(*x)--;
		}
		else 
			str = ft_chrjoin(str, line[*x]);
		(*x)++;
	}
	if (line[*x] && line[*x] == ' ')
	{
		ft_lstadd_back(lst, ft_lstnew(str));
		return (NULL);
	}
	return (str);
}
