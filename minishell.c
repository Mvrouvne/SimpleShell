/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:15 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/06 18:35:55 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexing2(char *line, token_t **lst, int *x)
{
	while (line[*x])
	{
		if  ((line[*x] >= 'a' && line[*x] <= 'z')
			|| (line[*x] >= 'A' && line[*x] <= 'Z'))
		{
			ft_lstadd_back(lst, ft_lstnew(&line[*x]));
		}
		(*x)++;
	}
	return (0);
}

int	lexing(char *line, token_t **lst, int *x)
{
	while (line[*x] == ' ' || line[*x] == '\t')
			(*x)++;
	// while (line[*x])
	// {	
		if ((line[*x] == '<' && line[*x + 1] == '<')
			|| (line[*x] == '>' && line[*x + 1] == '>'))
			ft_lstadd_back(lst, ft_lstnew("<<"));
		else if (line[*x] == '<' || line[*x] == '>')
			ft_lstadd_back(lst, ft_lstnew("<"));
		// else if ((line[*x] >= 'a' && line[*x] <= 'z')
		// 	|| (line[*x] >= 'A' && line[*x] <= 'Z'))
		// {
		// 	while ((line[*x] >= 'a' && line[*x] <= 'z')
		// 		|| (line[*x] >= 'A' && line[*x] <= 'Z'))
		// 	{
		// 		ft_lstadd_back(lst, ft_lstnew(&line[*x]));
		// 		(*x)++;
		// 	}
		// }
	// 	(*x)++;
	// }
	lexing2(line, lst, x);
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
	// while(1)
	// {
		line = readline("minishell: ");
		if (!line)
			exit (0);
		if (lexing(line, &lst, &x))
			exit (1);
	// }
	while (lst)
	{
		printf("lst = %s\n", lst->data);
		lst = lst->next;
	}
}
