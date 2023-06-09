/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:31 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/09 16:57:54 by machaiba         ###   ########.fr       */
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
	if ((d_count % 2 != 0 && s_count % 2 == 0)
		|| (s_count % 2 != 0 && s_count % 2 == 0))
	{
		write (2, "unclosed quote!\n", 17);
		exit (1);
	}
	while (line[*x] && line[*x] != ' ' && line[*x] != '|'
		&& line[*x] != '<' && line[*x] != '>')
	{
		if (line[0] == '~' && line[1] == '\0')
		{
			str2 = heredoc_expand(ft_strdup("$HOME"), env_parse, *lst);
			write(2, str2, ft_strlen(str2));
			write (2, ": is a directory\n", 18);
			exit (1);
		}
		else if (line[0] == '/' && line[1] == '\0')
		{
			write (2, "/: is a directory\n", 18);
			exit (1);
		}
		else if (line[*x] == '~' && (line[*x - 1] == ' ' || line[0] == '~')
			&& (line[*x + 1] == ' ' || line[*x + 1] == '\0'))
		{
			str2 = heredoc_expand(ft_strdup("$HOME"), env_parse, *lst);
			// printf("str2 = %s\n", str2);
			ft_lstadd_back(lst, ft_lstnew(str2));
			(*x)++;
			return (NULL);
		}
		else if (line[*x] == '"')
		{ 
			// (*lst)->av_quotes = 1;
			(*x)++;
			while (line[*x] && line[*x] != '"')
			{
				if (line[*x] == '$')
				{
					str2 = expand(*lst, line, x, env_parse);
					if (str2)
						str = ft_strjoin(str, str2);
				}
				if (line[*x] != '"')
					str = ft_chrjoin(str, line[*x]);
				else
					(*x)--;
				(*x)++;
			}
		}
		else if (line[*x] == '\'')
		{
			// (*lst)->av_quotes = 1;
			(*x)++;
			while (line[*x] && line[*x] != '\'')
			{
				str = ft_chrjoin(str, line[*x]);
				(*x)++;
			}
		}
		else if (line[*x] == '$')
		{
			str2 = expand(*lst, line, x, env_parse);
			if (str2)
				str = ft_strjoin(str, str2);
			(*x)--;
		}
		else 
			str = ft_chrjoin(str, line[*x]);
		(*x)++;
	}
	if (line[*x] && str[0] && (line[*x] == ' ' || line[*x] == '|'
		|| line[*x] == '<' || line[*x] == '>'))
	{
		ft_lstadd_back(lst, ft_lstnew(str));
		// if (d_count || s_count)
		// {
		// 	puts("iciiii");
		// 	(*lst)->av_quotes = 1;
		// 	printf("(*lst)->av_quotes = %d\n", (*lst)->av_quotes);
		// }
		// else
		// { 
		// 	(*lst)->av_quotes = 0;
		// }
		return (NULL);
	}
	return (str);
}
