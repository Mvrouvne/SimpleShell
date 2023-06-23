/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:13:26 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/23 04:45:41 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;

// void	handler(int num)
// {
// 	(void) num;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

char	**get_env_copy(t_list *saving_env)
{
	t_list	*tmp;
	char	**env_copy;
	int		i;

	tmp = saving_env;
	i = 0;
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

void	free_parser(t_args *args, t_token *lst)
{
	int		y;
	t_args	*args_temp;
	t_token	*lst_temp;

	if (args && args->args)
	{
		while (args)
		{
			y = 0;
			while (args->args[y])
			{
				free(args->args[y]);
				y++;
			}
			free(args->args);
			args_temp = args;
			args = args->next;
			free(args_temp);
		}
	}
	if (lst)
	{
		while (lst)
		{
			lst_temp = lst;
			lst = lst->next;
			free(lst_temp->data);
			free(lst_temp);
		}
	}
}

void	ft_execution(t_global *global, t_data *list, t_pipe *pipes)
{
	int	i;

	global->env_copy = get_env_copy(list->saving_env);
	implement_cmnd(list, global->args, global->env_copy, pipes);
	global->tmp = global->args;
	while (global->args->next)
	{
		close(pipes->fd[0]);
		close(pipes->fd[1]);
		global->args = global->args->next;
	}
	global->args = global->tmp;
	i = 0;
	while (i < pipes->cmds)
	{
		waitpid(list->pid[i], &g_exit_status, 0);
		i++;
	}
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	dup2(pipes->tmp, global->stdin_main);
	free(list->pid);
	ft_free(global->env_copy);
}
void	initialization(t_global *global, char **env, t_data *list,
		t_pipe *pipes)
{
	global->stdin_main = dup(0);
	list->saving_env = get_env(env);
	list->saving_expo = get_expo(env);
	(pipes->cmds = 0, pipes->tmp = dup(0));
	global->env_parse = (t_env *)list->saving_env;
	global->lst = NULL;
	global->args = NULL;
	global->env_copy = NULL;
}

void	initia_exec(t_global *global)
{
	global->lst = NULL;
	global->args = NULL;
	global->x = 0;
	global->line = readline("minishell:$> ");
}

int	main(int ac, char **av, char **env)
{
	t_global	global;
	t_data		*list;
	t_pipe		*pipes;

	(void)av;
	ac = 0;
	list = malloc(sizeof(t_data));
	pipes = malloc(sizeof(t_pipe));
	initialization(&global, env, list, pipes);
	while (1)
	{
		// signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, handler);
		initia_exec(&global);
		if (!global.line)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(global.line);
		if (!(lexing(global.line, &global.lst, &global.x, global.env_parse))
			&& (!(errors_check(global.lst)) && (!(split_args(global.lst,
							&global.args, global.env_parse)))))
			ft_execution(&global, list, pipes);
		free(global.line);
		free_parser(global.args, global.lst);
	}
	free(pipes);
}
