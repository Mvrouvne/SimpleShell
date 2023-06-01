
#include "minishell.h"

void	handler(int num)
{
	num = NULL;
	// exit (0);
}

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
	env_parse = (t_env *)saving_expo;
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
		args = NULL;
		x = 0;
		line = readline("minishell:$> ");
		signal(SIGINT, handler);
		if (!line)
			break ;
		add_history(line);
		if (!(lexing(line, &lst, &x, env_parse))
			&& (!(errors_check(lst)) && (!(split_args(&lst, &args, env_parse)))))
			execution(&args, &saving_env, &saving_expo, env);
			// continue;
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
