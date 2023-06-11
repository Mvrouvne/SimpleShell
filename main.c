
#include "minishell.h"

// void	handler(int num)
// {
// 	(void) num;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*lst;
	t_args	*args;
	int		x;
	(void) av;
	t_list	*saving_expo;
	t_list	*saving_env;
	t_pipe	*pipes;
	t_env	*env_parse;

	pipes = malloc(sizeof(t_pipe));
	saving_env = get_env(env);
	saving_expo = saving_env;
	pipes->cmds = 0;
	pipes->tmp = dup(0);
	env_parse = (t_env *)saving_expo;
	int stdin_main = dup(0);
	ac = 0;
	x = 0;
	lst = NULL;
	args = NULL;
	
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, handler);
	while(1)
	{
		lst = NULL;
		args = NULL;
		x = 0;
		line = readline("minishell:$> ");
		if (!line)
		{
			printf("exit ohibok\n");
			exit (0);
		}
		add_history(line);
		if (!(lexing(line, &lst, &x, env_parse))
			&& (!(errors_check(lst)) && (!(split_args(&lst, &args, env_parse)))))
		{
			// printf("p->args = %s\n", args->args[0]);
			// printf("p->args = %s\n", args->args[1]);
			// printf("p->args = %s\n", args->args[2]);
			exit(0);
			execution(&args, &saving_env, &saving_expo, env, pipes);
			while (args->next)
			{
				close(pipes->fd[0]);			////////////// ana hna
				close(pipes->fd[1]);
				args = args->next;
			}
			while (wait(NULL) != -1);
			dup2(pipes->tmp, stdin_main);
		}
		// system("leaks minishell");
		free (line);
	}
	// while (lst)
	// {
	// 	printf("lst = %s\n", lst->data);
	// 	lst = lst->next;
	// }
	// write(1, "\n", 1);
	// int	t = 0;
	// while (args)
	// {
	// 		t = 0;
	// 		while (args->args[t])
	// 			printf("args = %s\n", args->args[t++]);
	// 		printf("infile = %d\n", args->infile);
	// 		printf("outfile = %d\n", args->outfile);
	// 		printf("****************\n");
	// 	args = args->next;
	// }
}
