/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:15 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/06 23:01:40 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexing3(char *line, token_t **lst, int *x)
{
	char	*str;

	str = malloc(sizeof(char) + 1);
	if (line[*x] == '<' || line[*x] == '>' || line[*x] == '|')
	{
		str[0] = line[*x];
		ft_lstadd_back(lst, ft_lstnew(str));
		str[1] = '\0';
		(*x)++;
	}
	return (0);
}

int	lexing2(char *line, token_t **lst, int *x)
{
	char	*str;
	int		y;
	y = 0;
	y = *x;
	while (line[y])
	{
		if  (line[*x] == '<' || line[*x] == '>'
			|| line[*x] == '|') 
			break ;
		y++;
	}
	str = malloc(sizeof(char) * (y + 1));
	y = 0;
	while (line[*x])
	{
		if  (line[*x] == '<' || line[*x] == '>'
			|| line[*x] == '|') 
			break ;
		str[y] = line[*x];
		y++;
		(*x)++;
	}
	str[y] = '\0';
	ft_lstadd_back(lst, ft_lstnew(str));
	return (0);
}

int	lexing(char *line, token_t **lst, int *x)
{
	while (line[*x] == ' ' || line[*x] == '\t')
		(*x)++;
	if (line[*x] == '<' && line[*x + 1] == '<')
	{
		ft_lstadd_back(lst, ft_lstnew("<<"));
		(*x)++;
	}
	else if (line[*x] == '<')
	{
		ft_lstadd_back(lst, ft_lstnew("<"));
		(*x)++;
	}
	while (line[*x])
	{
		while (line[*x] == ' ' || line[*x] == '\t')
			(*x)++;
		lexing2(line, lst, x);
		lexing3(line, lst, x);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	token_t	*lst;
	int		x;
	(void) env;
	(void) av;

	ac = 0;
	// int	x = 0;
	// int	y = 0;
	x = 0;

	lst = NULL;
	while(1)
	{
		line = readline("minishell: ");
		if (!line)
			break ;
		if (lexing(line, &lst, &x))
			exit (1);
	}
	write(1, "\n", 1);
	while (lst)
	{
		printf("lst = %s\n", lst->data);
		lst = lst->next;
	}
}
