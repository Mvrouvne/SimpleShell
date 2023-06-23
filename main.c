/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:13:26 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/22 22:32:37 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

void	handler(int num)
{
	(void) num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char **get_env_copy(t_list *saving_env)
{
	t_list *tmp;
	char **env_copy;
	
	tmp = saving_env;
	int i = 0;
	while (saving_env)
	{
		i++;
		saving_env = saving_env->next;
	}
	saving_env = tmp;
	env_copy = malloc(sizeof(char *) * (i + 1));
	env_copy[i] = NULL;
	i = 0;
	while (saving_env)
	{
		env_copy[i] = ft_strdup(saving_env->value);
		i++;
		saving_env = saving_env->next;
	}
	saving_env = tmp;
	return (env_copy);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*lst;
	t_token	*lst_temp;
	t_args	*args;
	t_args	*tmp;
	t_args	*args_temp;
	int		x;
	int		y;
	(void) av;
	t_data *list;
	t_pipe	*pipes;
	t_env	*env_parse;
	char **env_copy = NULL;

	list = malloc(sizeof(t_data));
	pipes = malloc(sizeof(t_pipe));
	
	list->saving_env = get_env(env);
	list->saving_expo = get_expo(env);
	
	(pipes->cmds = 0, pipes->tmp = dup(0));
	
	env_parse = (t_env *)list->saving_env;
	int stdin_main = dup(0);
	ac = 0;
	x = 0;
	y = 0;
	lst = NULL;
	args = NULL;
	while(1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		lst = NULL;
		args = NULL;
		x = 0;
		y = 0;
		line = readline("minishell:$> ");
		if (!line)
		{
			printf("exit\n"); 
			exit (0);
		}
		add_history(line);
		if (!(lexing(line, &lst, &x, env_parse))
			&& (!(errors_check(lst)) && (!(split_args(lst, &args, env_parse)))))
		{
			env_copy = get_env_copy(list->saving_env);
			implement_cmnd(list, args, env_copy, pipes);
			tmp = args;
			while (args->next)
			{
				close(pipes->fd[0]);
				close(pipes->fd[1]);
				args = args->next;
			}
			args = tmp;
			int i = 0;
			while (i < pipes->cmds)
			{
				waitpid(list->pid[i], &g_exit_status, 0);
				i++;
			}
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
			dup2(pipes->tmp, stdin_main);
			free(list->pid);
			ft_free(env_copy);
		}
		free (line);
		// free (args->args[0]);
		// free (args->args);
		if (args && args->args)
		{
			// if (args->args[0])
			// {
				while (args)
				{
					y = 0;
					while (args->args[y])
					{
						free(args->args[y]);
						y++;
					}
					free (args->args);
					args_temp = args;
					args = args->next;
					free (args_temp);
				}
			// }
			// else if ((!args->args[0]))
			// {
			// 	free (args->args[0]);
			// 	puts("HEEREE");
			// 	while (args)
			// 	{
			// 		free (args->args);
			// 		args_temp = args;
			// 		args = args->next;
			// 		free (args_temp);
			// 	}
			// }
		}
		if (lst)
		{
			// lst_temp = lst;
			// while (lst_temp)
			// {
			// 	lst_temp = lst_temp->next;
			// }
			while (lst)
			{
				lst_temp = lst;
				lst = lst->next;
				free (lst_temp->data);
				free(lst_temp);
			}
		}
	}

	// while (list->saving_env)
	// {
	// 	free (list->saving_env->value);
	// 	list->saving_env = list->saving_env->next;
	// }
	// free(list);
	free(pipes);
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
