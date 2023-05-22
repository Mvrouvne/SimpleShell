/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:31 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/22 16:18:57 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_quotes(t_token **lst, char *line, int *x, t_env *env_parse)
{
	char *str;
	char *str2;
	// int	d_quote;
	// int	s_quote;
	// int	d_count;
	// int	s_count;
	// int	temp;
	int	y;

	// y = *x;
	// while (line[*x] == '"')
	// 	(*x)++;
	// if (line[*x] == '$')
	// 	return (0);
	// else
	// 	*x = y;
	// d_count = 0;
	// s_count = 0;
	// if (!str2)
	// {
		str = malloc(sizeof(char));
		str[0] = '\0';
	// }
	// else
	// {
	// 	str = malloc(sizeof(char) * ft_strlen(str) + 1);
	// 	str = str2;
	// }
	// str[0] = '\0';
	// d_quote = 0;
	// s_quote = 0;
	// temp = *x;
	// while(line[*x])
	// {
	// 	if (line[*x] == '"')
	// 		d_count++;
	// 	else if (line[*x] == '\'')
	// 		s_count++;
	// 	(*x)++;
	// }
	// *x = temp;
	y = 0;
	while (line[*x] && line[*x] != ' ')
	{
		// printf("line[x] = %c\n", line[*x]);
		if (line[*x] == '"')
		{
			(*x)++;
			while (line[*x] && line[*x] != '"')
			{
				if (line[*x] == '$')
				{
					// y++;
					// (*x)--;
					// break ;
					str2 = expand(lst, line, x, env_parse);;
					str = ft_strjoin(str, str2);
				}
				str = ft_chrjoin(str, line[*x]);
				(*x)++;
			}
		}
		else if (line[*x] == '\'')
		{
			(*x)++;
			while (line[*x] && line[*x] != '\'')
			{
				// if (line[*x] == '$')
				// {
				// 	(*x)--;
				// 	break ;
				// }
				str = ft_chrjoin(str, line[*x]);
				(*x)++;
			}
		}
		else if (line[*x] == '$')
		{
			str2 = expand(lst, line, x, env_parse);
			str = ft_strjoin(str, str2);
		}
		else 
			str = ft_chrjoin(str, line[*x]);
		(*x)++;
	}
			// printf("str = %s\n", str);
	// while (line[*x] && line[*x] == ' ')
	// 	(*x)++;
	// printf("str = %s\n", str);
	// if (str)
	// {
	// 	// if (count % 2 != 0)
	// 	// {
	// 	// 	write(2, "quote not closed!\n", 19);
	// 	// 	exit (1);
	// 	// }
	// 	ft_lstadd_back(lst, ft_lstnew(str));
	// }
	return (str);
}
