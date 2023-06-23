/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:31 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/23 03:07:31 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_quotes4(t_token **lst, char *line, int *x, char *str)
{
	extern int	g_exit_status;

	(*x)++;
	while (line[*x] && line[*x] != '\'')
	{
		str = ft_chrjoin(str, line[*x]);
		(*x)++;
	}
	if (line[*x] != '\'')
	{
		write(2, "syntax error near unexpected token`unclosed quote'\n", 52);
		g_exit_status = 258;
		return (NULL);
	}
	else if (line[*x] == '\'' && !str[0])
		ft_lstadd_back(lst, ft_lstnew(str));
	return (str);
}

void	check_quotes3(t_env *env_parse, char *str)
{
	char	*str2;
	int		x;

	x = 0;
	str2 = heredoc_expand(ft_strdup("$HOME"), env_parse, x);
	write(2, str2, ft_strlen(str2));
	write (2, ": is a directory\n", 18);
	free (str);
	free (str2);
}

char	*check_quotes2(char *line, int *x, t_token **lst, t_env *env_parse)
{
	char	*str;
	char	*str2;

	(*x)++;
	while (line[*x] && line[*x] != '"')
	{
		if (line[*x] == '$')
		{
			str2 = expand(*lst, line, x, env_parse);
			if (str2)
			{
				free (str);
				str = ft_strjoin(str, str2);
				free (str2);
			}
			else
				free (str2);
		}
		if (line[*x] != '"')
			str = ft_chrjoin(str, line[*x]);
		else
			(*x)--;
		(*x)++;
	}
	return (str);
}

int	check_quotes(t_token **lst, char *line, int *x, t_env *env_parse)
{
	t_var		var;
	extern int	g_exit_status;

	var.str = ft_strdup("");
	var.line = line;
	var.check = check_quotes_follow(line, x, lst);
	while (line[*x] && line[*x] != ' ' && line[*x] != '|'
		&& line[*x] != '<' && line[*x] != '>')
	{
		if (check_quotes_follow6(x, lst, env_parse, &var))
			return (1);
		(*x)++;
	}
	if (var.str[0])
		ft_lstadd_back(lst, ft_lstnew(var.str));
	return (free (var.str), 0);
}
