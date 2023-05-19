/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:28:21 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/19 21:16:12 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*lst;
	t_args	*args;
	int		x;
	(void) av;
	t_list	*saving_expo;
	t_list	*saving_env;
	t_env	*env_parse;
	
	saving_env = get_env(env);
	saving_expo = get_env(env);
	env_parse = (t_env *)get_env(env);
	ac = 0;
	// int	x = 0;
	// int	y = 0;
	x = 0;
	lst = NULL;
	args = NULL;
	// args = malloc(sizeof(t_token));
	// t_args = args;
	while(1)
	{
		lst = NULL;
		x = 0;
		line = readline("minishell:$> ");
		if (!line)
			break ;
		add_history(line);
		lexing(line, &lst, &x, env_parse);
		split_args(&lst, &args);
		execution(&args, &saving_env, &saving_expo);
		free (line);
		// while (lst)
		// {
		// 	temp = lst;
		// 	lst = lst->next;
		// 	free(temp->data);
		// 	free(temp);
		// }
	}
	write(1, "\n", 1);
	int	t = 0;
	while (args)
	{
			t = 0;
			while (args->args[t])
				printf("args = %s\n", args->args[t++]);
			printf("infile = %d\n", args->infile);
			printf("outfile = %d\n", args->outfile);
			printf("****************\n");
		args = args->next;
	}
	// while (lst)
	// {
	// 	printf("type = %d\n", lst->type);
	// 	lst = lst->next;
	// }
}
