/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:46:19 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/17 22:20:52 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	lexing3(t_token	**lst)
{
	t_token	*temp;

	temp = *lst;
	while (temp)
	{
		if (temp->next && (!(ft_strncmp(temp->data, "<<", 2))))
		{
			temp->type = HEREDOC;
			temp->next->type = DELIMITER;
			temp = temp->next;
		}
		else if (temp->next && (!(ft_strncmp(temp->data, ">>", 2))))
		{
			temp->type = APPEND;
			temp->next->type = APPEND;
			temp = temp->next;
		}
		else if (temp->next && (!(ft_strncmp(temp->data, "<", 1))))
		{
			temp->type = INPUT;
			temp->next->type = INPUT;
			temp = temp->next;
		}
		else if (temp->next && (!(ft_strncmp(temp->data, ">", 1))))
		{
			temp->type = OUTPUT;
			temp->next->type = OUTPUT;
			temp = temp->next;;
		}
		else if (!(ft_strncmp(temp->data, "|", 1)))
			temp->type = PIPE;
		else
			temp->type = CMD;
		temp = temp->next;
	}
	return (0);
}

int	lexing(char *line, t_token **lst, int *x, t_env *env_parse)
{
	int		z;
	int		w;

	z = 0;
	w = 0;
	if (!(ft_strcmp(line, "\0")))
		return (1);
	while (line[*x] == ' ' || line[*x] == '\t')
		(*x)++;
	while (line[*x])
	{
		while (line[*x] && (line[*x] == ' ' || line[*x] == '\t'))
			(*x)++;
		if (check_quotes(lst, line, x, env_parse))
			return (1);
		lexing2(line, lst, x);
	}
	lexing3(lst);
	return (0);
}
