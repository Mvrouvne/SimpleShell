/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:31 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/22 15:33:38 by machaiba         ###   ########.fr       */
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
		// free (str);
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

	str2 = heredoc_expand(ft_strdup("$HOME"), env_parse);
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
	char	*str;
	char	*str2;
	int		y;
	int		a;
	int		check;
	extern int	g_exit_status;
	
	str = malloc(sizeof(char));
	str[0] = '\0';
	y = 0;

	a = 0;
	check = 0;
	while (line[a])
	{
		if (line[a] == '<' && line[a + 1] == '<')
		{
			check++;
			break ;
		}
		a++;
	}
	if (line[*x] == '|')
	{
		ft_lstadd_back(lst, ft_lstnew("|"));
		(*x)++;
	}
	while (line[*x] && line[*x] != ' ' && line[*x] != '|'
		&& line[*x] != '<' && line[*x] != '>')
	{
		if (line[0] == '~' && (line[1] == '\0' || line[1] == ' '))
		{
			check_quotes3(env_parse, str);
			return (1);
		}
		else if (line[0] == '/' && line[1] == '\0')
		{
			write (2, "/: is a directory\n", 18);
			return (free (str), 1);
		}
		else if (line[*x] == '~' && (line[*x - 1] == ' ' || line[0] == '~')
			&& (line[*x + 1] == ' ' || line[*x + 1] == '\0'))
		{
			str2 = heredoc_expand(ft_strdup("$HOME"), env_parse);
			ft_lstadd_back(lst, ft_lstnew(str2));
			(*x)++;
			return (free (str), free (str2), 0);
		}
		else if (line[*x] == '$' && line[*x + 1] == '?')
		{
			// free (str);
			str = ft_join_free(str, ft_itoa(g_exit_status));
			(*x)++;
		}
		else if (line[*x] == '"')
		{
			(*x)++;
			while (line[*x] && line[*x] != '"')
			{
				if (line[*x] == '$' && !check)
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
			if (line[*x] != '"')
			{
				free (str);
				write(2, "syntax error near unexpected token`unclosed quote'\n", 52);
				g_exit_status = 258;
				return (g_exit_status);
			}
			else if (line[*x] == '"' && !str[0])
				ft_lstadd_back(lst, ft_lstnew(str));
		}
		else if (line[*x] == '\'')
		{
			str = check_quotes4(lst, line, x, str);
			if (!str)
				return (1);
		}
		else if (line[*x] == '$' && !check)
		{
			str2 = expand(*lst, line, x, env_parse);
			if (str2)
			{
				free (str);
				str = ft_strjoin(str, str2);
				free(str2);
			}
			else
				free (str2);
			(*x)--;
		}
		else 
			str = ft_chrjoin(str, line[*x]);
		(*x)++;
	}
	if (str[0])
		ft_lstadd_back(lst, ft_lstnew(str));
	free (str);
	return (0);
}
