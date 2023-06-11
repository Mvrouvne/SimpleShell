
#include "parsing.h"

int	split_args(t_token **lst, t_args **args, t_env *env_parse)
{
	t_token	*temp;
	t_args	*temp2;
	int		x;
	int		y;
	int		z;
	int		in;
	int		out;
	int		max;

	y = 0;
	z = 0;
	in = 0;
	out = 0;
	max = 0;
	t_token *tmp = *lst;
	while (tmp)
	{
		if (tmp->av_quotes != 1)
			tmp->av_quotes = 0;
		tmp = tmp->next;
	}
	temp = *lst;
	create_list(args, *lst);
	(*args)->args = malloc(sizeof(char *));
	(*args)->args[0] = NULL;
	temp2 = *args;
	while (temp && *args)
	{
		if (temp->next && temp->type == INPUT)
		{
			in = 1;
			(*args)->infile = open(temp->next->data, O_RDWR);
			if ((*args)->infile == -1)
			{
				perror(temp->next->data);
				return (1);
			}
			temp = temp->next;
		}
		else if (temp->next && temp->type == OUTPUT)
		{
			out = 1;
			(*args)->outfile = open(temp->next->data, O_RDWR | O_CREAT | O_TRUNC, 0777);
			if ((*args)->outfile == -1)
			{
				perror(temp->next->data);
				return (1);
			}
			temp = temp->next;
		}
		else if (temp->next && temp->type == APPEND)
		{
			out = 2;
			(*args)->outfile = open(temp->next->data, O_RDWR | O_CREAT | O_APPEND, 0777);
			if ((*args)->outfile == -1)
			{
				perror(temp->next->data);
				return (1);
			}
			temp = temp->next;
		}
		else if (temp->type == CMD || temp->type == PIPE)
		{
			if (temp->type == PIPE)
			{
				y = 0;
				*args = (*args)->next;
				x = 0;
				z = 0;
				in = 0;
				x = args_count(*lst);
				(*args)->args = malloc(sizeof(char *) * (x + 1));
				z++;
				(*args)->args[x] = NULL;
			}
			else
			{
				if (!y && !z)
				{
					x = 0;
					x = args_count(*lst);
					(*args)->args = malloc(sizeof(char *) * (x + 1));
					(*args)->args[x] = NULL;
				}
				(*args)->args[y] = ft_strdup(temp->data);
				y++;
			}
			check_in_out(*args, in, out);
		}
		else if (temp->type == DELIMITER)
		{
			printf("max = %d\n", max);
			if (max >= 16)
			{
				write (2, "maximum here-document count exceeded\n", 38);
				exit (2);
			}
			max++;
			heredoc(*args, temp->data, env_parse, *lst);
		}
		temp = temp->next;
	}
	*args = temp2;
	return (0);
}

int	lexing4(t_token	**lst)
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
		else if (temp->next && (!(ft_strncmp(temp->next->data, "<<", 2))))
			temp->type = CMD;
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

int	lexing3(char *line, t_token **lst, int *x)
{
	char	*str;
	int		check;
	int		y;

	check = 0;
	y = 0;
	if ((line[*x] == '<' && line[*x + 1] == '<')
		|| (line[*x] == '>' && line[*x + 1] == '>'))
	{
		y = *x;
		y += 2;
		while (line[y] == ' ' || line[y] == '\t')
			y++;
		while (line[y] && line[y] != '>' && line[y] != '<' && line[y] != '|')
		{
			if (line[y] == '"' || line[y] == '\'')
			{
				check = 1;
				break ;
			}
			y++;
		}
		str = malloc(sizeof(char) * 3);
		if (!str)
			exit (1);
		str[0] = line[*x];
		str[1] = line[*x + 1];
		str[2] = '\0';
		ft_lstadd_back(lst, ft_lstnew(str));
		if (check)
			(*lst)->av_quotes = 1;
		(*x) += 2;
		// free (str);
	}
	else if (line[*x] == '<' || line[*x] == '>')
	{
		str = malloc(sizeof(char) + 1);
		if (!str)
			exit (1);
		str[0] = line[*x];
		str[1] = '\0';
		ft_lstadd_back(lst, ft_lstnew(str));
		// free (str);
		(*x)++;
	}
	return (0);
}

// int	lexing2(char *line, t_token **lst, int *x, t_env *env_parse)
// {
// 	(void) env_parse;
// 	char	*str;
// 	int		y;
// 	int		z;

// 	y = *x;
// 	z = 0;
// 	while (line[y])
// 	{
// 		if  (line[*x] == '<' || line[*x] == '>'
// 			|| line[*x] == '|' || line[*x] == ' '
// 			|| line[*x] == '"' || line[*x] == '\''
// 			|| line[*x] == '$')
// 			break ;
// 		y++;
// 	}
// 	if (y)
// 	{
// 		str = malloc(sizeof(char) * y + 1);
// 		if (!str)
// 			exit (1);
// 	}
// 	y = 0;
// 	while (line[*x])
// 	{
// 		if  (line[*x] == '<' || line[*x] == '>'
// 			|| line[*x] == '|' || line[*x] == ' '
// 			|| line[*x] == '$' || line[*x] == '"'
// 			|| line[*x] == '\'')
// 			break ;
// 		str[y] = line[*x];
// 		y++;
// 		(*x)++;
// 	}
// 	if (y)
// 	{
// 		str[y] = '\0';
// 		(*x)++;
// 		ft_lstadd_back(lst, ft_lstnew(str));
// 	}
// 	return (0);
// }

int	lexing(char *line, t_token **lst, int *x, t_env *env_parse)
{
	// char	*str;
	// char	*str2 = NULL;
	int		z;
	int		w;

	z = 0;
	w = 0;
	if (ft_strcmp(line, "\0") == 0)
		return (1);
	while (line[*x] == ' ' || line[*x] == '\t')
		(*x)++;
	// if (line[*x] == '<' && line[*x + 1] == '<')
	// {
	// 	ft_lstadd_back(lst, ft_lstnew("<<"));
	// 	(*x) += 2;
	// }
	// else if (line[*x] == '<')
	// {
	// 	ft_lstadd_back(lst, ft_lstnew("<"));
	// 	(*x)++;
	// }
	while (line[*x])
	{
		// printf("line[*x] = [%c]\n", line[*x]);
		while (line[*x] && (line[*x] == ' ' || line[*x] == '\t'))
			(*x)++;
		// lexing2(line, lst, x, env_parse);
		if (check_quotes(lst, line, x, env_parse))
			return (1);
		// if(str)
		// {
		// 	str2 = ft_strjoin(str2, str);
		// 	if (str2[0])
		// 		ft_lstadd_back(lst, ft_lstnew(str2));
		// }
		lexing3(line, lst, x);
		// exit (1);
	}
	lexing4(lst);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	t_token	*lst;
// 	t_args	*args;
// 	int		x;
// 	(void) env;
// 	(void) av;

// 	ac = 0;
// 	// int	x = 0;
// 	// int	y = 0;
// 	x = 0;
// 	lst = NULL;
// 	args = NULL;
// 	// args = malloc(sizeof(t_token));
// 	// t_args = args;
// 	while(1)
// 	{
// 		lst = NULL;
// 		x = 0;
// 		line = readline("minishell:$> ");
// 		if (!line)
// 			break ;
// 		add_history(line);
// 		lexing(line, &lst, &x);
// 		split_args(&lst, &args);
// 		// execution(args, env);
// 		free (line);
// 		// while (lst)
// 		// {
// 		// 	temp = lst;
// 		// 	lst = lst->next;
// 		// 	free(temp->data);
// 		// 	free(temp);
// 		// }
// 	}
// 	write(1, "\n", 1);
// 	int	t = 0;
// 	while (args)
// 	{
// 			t = 0;
// 			while (args->args[t])
// 				printf("args = %s\n", args->args[t++]);
// 			printf("infile = %d\n", args->infile);
// 			printf("outfile = %d\n", args->outfile);
// 			printf("****************\n");
// 		args = args->next;
// 	}
// 	// while (lst)
// 	// {
// 	// 	printf("type = %d\n", lst->type);
// 	// 	lst = lst->next;
// 	// }
// }
