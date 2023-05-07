/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:15 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/07 19:55:14 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	lexing4(t_token	**lst)
// {
// 	t_token	*temp;

// 	temp = *lst;
// 	// while (temp)
// 	// {
// 			// printf("temp = %s\n", temp->data);
// 		if (!(ft_strncmp(temp->data, "<", 1)))
// 		{
// 			while (*lst)
// 			{
// 			printf("HEEEREEE\n");
// 				if (temp->data == (*lst)->data)
// 					(*lst)->type = L_OP;
// 				*lst = (*lst)->next;
// 			}
// 		}
// 		// else if ()
// 	// }
// 	return (0);
// }

int	lexing3(char *line, t_token **lst, int *x)
{
	char	*str;

	while (line[*x] == ' ' || line[*x] == '\t')
		(*x)++;
	if ((line[*x] == '<' && line[*x + 1] == '<')
		|| (line[*x] == '>' && line[*x + 1] == '>'))
	{
		str = malloc(sizeof(char) + 2);
		str[0] = line[*x];
		str[1] = line[*x + 1];
		str[2] = '\0';
		ft_lstadd_back(lst, ft_lstnew(str));
		(*x) += 2;
	}
	else if (line[*x] == '<' || line[*x] == '>' || line[*x] == '|')
	{
		str = malloc(sizeof(char) + 1);
		str[0] = line[*x];
		str[1] = '\0';
		ft_lstadd_back(lst, ft_lstnew(str));
		(*x)++;
	}
	return (0);
}

int	lexing2(char *line, t_token **lst, int *x)
{
	char	*str;
	int		y;

	y = *x;
	while (line[y])
	{
		if  (line[*x] == '<' || line[*x] == '>'
			|| line[*x] == '|' || line[*x] == ' ')
			break ;
		y++;
	}
	if (y)
	{
		str = malloc(sizeof(char) * y + 1);
		if (!str)
			exit (1);
	}
	y = 0;
	while (line[*x])
	{
		if  (line[*x] == '<' || line[*x] == '>'
			|| line[*x] == '|' || line[*x] == ' ')
			break ;
		str[y] = line[*x];
		y++;
		(*x)++;
	}
	if (y)
	{
		str[y] = '\0';
		ft_lstadd_back(lst, ft_lstnew(str));
	}
	return (0);
}

int	lexing(char *line, t_token **lst, int *x)
{
	while (line[*x] == ' ' || line[*x] == '\t')
		(*x)++;
	if (line[*x] == '<' && line[*x + 1] == '<')
	{
		ft_lstadd_back(lst, ft_lstnew("<<"));
		(*x) += 2;
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
	t_token	*lst;
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
		line = readline("minishell:$> ");
		if (!line)
			break ;
		// printf("line = %s\n", line);
		lexing(line, &lst, &x);
		// lexing4(&lst);
	}
	write(1, "\n", 1);
	// while (lst)
	// {
		printf("lst = %s\n", lst->data);
		lst = lst->next;
		// printf("type = %d\n", ls`t->type);
	// }
}
