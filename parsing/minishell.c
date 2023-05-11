/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:15 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/11 23:10:30 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_list(t_token **lst, t_args **args)
{
	t_token	*temp;
	char 	*str;

	temp = *lst;
	while (temp)
	{
		if (temp->data[0] != '|')
		{
			str = ft_strdup(temp->data);
			ft_lstadd_back2(args, ft_lstnew(str));
			free (str);
		}
		temp = temp->next;
	}
	return (0);
}

int	split_args(t_token **lst, t_args **args)
{
	t_token	*temp;
	// char	*str;
	int		x;
	int		y;
	int		z;

	x = 0;
	y = 0;
	z = 0;
	temp = *lst;
	(*args)->args = malloc(sizeof(char *));
	while (temp)
	{
		if (temp->type == INPUT)
		{
			(*args)->infile = open(temp->next->data, O_RDWR);
			if ((*args)->infile == -1)
			{
				write(2, "Error\n", 7);
				exit(1);
			}
			temp = temp->next;
		}
		else if (temp->type == OUTPUT)
		{
			(*args)->outfile = open(temp->next->data, O_RDWR | O_CREAT | O_TRUNC, 0777);
			if ((*args)->outfile == -1)
			{
				write(2, "Error\n", 7);
				exit(1);
			}
			temp = temp->next;
		}
		else if (temp->type == APPEND)
		{
			(*args)->outfile = open(temp->next->data, O_RDWR | O_CREAT | O_APPEND, 0777);
			if ((*args)->outfile == -1)
			{
				write(2, "Error\n", 7);
				exit(1);
			}
			temp = temp->next;
		}
		else if (temp->type == CMD)
		{
			(*args)->args[y] = ft_strdup(temp->data);
			printf("args = %s\n", (*args)->args[y]);
			y++;
		}
		temp = temp->next;
	}
	// split_list(lst, args);
	return (0);
}

int	lexing4(t_token	**lst)
{
	t_token	*temp;

	temp = *lst;
	while (temp)
	{
		if (!(ft_strncmp(temp->data, "<", 1)))
			temp->type = INPUT;
		// if (temp->next && (!(ft_strncmp(temp->data, "<", 1))))
		// 	temp->next->type = INPUT;
		if (!(ft_strncmp(temp->data, ">", 1)))
			temp->type = OUTPUT;
		// if (temp->next && (!(ft_strncmp(temp->data, ">", 1))))
		// 	temp->next->type = OUTPUT;
		if (!(ft_strncmp(temp->data, "|", 1)))
			temp->type = PIPE;
		// if (temp->next && (!(ft_strncmp(temp->data, "|", 1))))
		// 	temp->next->type = CMD;
		// if (temp->next && (!(ft_strncmp(temp->next->data, "|", 1))))
		// 	temp->type = CMD;
		if (!(ft_strncmp(temp->data, "<<", 2)))
			temp->type = HEREDOC;
		if (temp->next && (!(ft_strncmp(temp->data, "<<", 2))))
			temp->next->type = DELIMITER;
		// if (!(ft_strncmp(temp->data, ">>", 2)))
		// 	temp->type = APPEND;
		if (temp->next && (!(ft_strncmp(temp->data, ">>", 2))))
			temp->next->type = APPEND;
		// if (temp->next && (!(ft_strncmp(temp->next->data, "-", 1))))
		// 	temp->next->type = ARG;
		temp = temp->next;
	}
	return (0);
}

int	lexing3(char *line, t_token **lst, int *x)
{
	char	*str;

	if ((line[*x] == '<' && line[*x + 1] == '<')
		|| (line[*x] == '>' && line[*x + 1] == '>'))
	{
		str = malloc(sizeof(char) * 3);
		if (!str)
			exit (1);
		str[0] = line[*x];
		str[1] = line[*x + 1];
		str[2] = '\0';
		ft_lstadd_back(lst, ft_lstnew(str));
		(*x) += 2;
	}
	else if (line[*x] == '<' || line[*x] == '>' || line[*x] == '|')
	{
		str = malloc(sizeof(char) + 1);
		if (!str)
			exit (1);
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
			|| line[*x] == '|' || line[*x] == ' '
			|| line[*x] == '"' || line[*x] == '\'')
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
			|| line[*x] == '|' || line[*x] == ' '
			|| line[*x] == '"' || line[*x] == '\'')
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
	char	*str;
	int		y;
	int		tmp;

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
		if (line[*x] == '"' || line[*x] == '\'')
		{
			(*x)++;
			tmp = *x;
			while (line[*x] != '"' && line[*x] != '\'')
			{
				y++;
				(*x)++;
			}
			*x = tmp;
			str = malloc(sizeof(char) * (y + 1));
			y = 0;
			while (line[*x] != '"' && line[*x] != '\'')
			{
				str[y] = line[*x];
				y++;
				(*x)++;
			}
			(*x)++;
			ft_lstadd_back(lst, ft_lstnew(str));
		}
		lexing2(line, lst, x);
		lexing3(line, lst, x);
	}
	lexing4(lst);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*lst;
	t_args	*args;
	int		x;
	(void) env;
	(void) av;

	ac = 0;
	// int	x = 0;
	// int	y = 0;
	x = 0;
	lst = NULL;
	args = malloc(sizeof(t_token));
	while(1)
	{
		x = 0;
		line = readline("minishell:$> ");
		add_history(line);
		if (!line)
			break ;
		lexing(line, &lst, &x);
		split_args(&lst, &args);
	}
	write(1, "\n", 1);
	// while (lst)
	// {
	// 	printf("lst = %s\n", lst->data);
	// 	printf("type = %d\n", lst->type);
	// 	lst = lst->next;
	// }
	while (args)
	{
		printf("args = %s\n", args->data);
		args = args->next;
	}
	printf("infile = %d\n", args->infile);
	printf("outfile = %d\n", args->outfile);
}
