/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:23:27 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/16 20:22:35 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_n(char *str)
{
	int	i;

	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (2);
}

void	echo(char **p)
{
	int	i;

	i = 1;
	if (p[i] == NULL)
		return ;
	while (p[i])
	{
		if (check_n(p[i]) == 0 && i > 1 && check_n(p[i - 1]) != 0)
			printf("%s ", p[i]);
		else if (check_n(p[i]) == 1)
			printf("%s ", p[i]);
		else if (check_n(p[i]) == 2)
			printf("%s ", p[i]);
		i++;
	}
	if (check_n(p[1]) == 1 || check_n(p[1]) == 2)
		printf("\n");
}

int	cd(char **p, t_list *saving_expo)
{
	/////////*****************
	if (search_home(saving_expo, "HOME") == 0)
	{
		perror("minishell: cd");
		return (0);
	}
	else if (p[1] == NULL && search_home(saving_expo, "HOME") == 1)
	{
		puts("samaykom");
		chdir(getenv("HOME"));
	}
	else if ((!ft_strcmp(p[1], "~")) && search_home(saving_expo, "HOME") == 1)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else if (chdir(p[1]))
	{
		perror("minishell: cd");
		return (0);
	}
	return (1);
}

void	unset(t_list **head, char *key)
{
	t_list	*cur;
	t_list	*prev;
	//int result;

	cur = (*head);
	prev = NULL;
	
	//search for the node in my lincked list
	while(cur && cur->next != NULL && ft_strncmp(cur->value, key, ft_strlen(key)))
	{
		prev = cur;
		cur = cur->next;
	}
	//if the node we re looking for is the first node///that means prev still have NULL value
	if (prev == NULL && cur )
		(*head) = cur->next;
	//if the node we re locking for is in the middle or in the end///that means the prev node is before the cur node
	else if (cur && prev && ft_strncmp(cur->value, key, ft_strlen(key)) == 0)
		prev->next = cur->next;
	// free (cur);
}


t_list	*search_OldPwd(t_list *saving_env)
{
	t_list	*tmp;
	
	tmp = saving_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "OLDPWD=", 7) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
t_list	*search_Pwd(t_list *saving_env)
{
	t_list	*tmp;
	
	tmp = saving_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "PWD=", 4) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_OldPwd(t_list **saving_env, char *old_pwd)
{
	t_list	*new;
	(void) saving_env;
	char	str[8] = "OLDPWD=";
	int		i;
	char	*new_str;
	t_list	*oldpwd_found;
	
	oldpwd_found = search_OldPwd(*saving_env);
	if (oldpwd_found != NULL)
		oldpwd_found->value = ft_strjoin("OLDPWD=", old_pwd);
	else
	{
		i = ft_strlen(old_pwd) + ft_strlen(str) + 1;
		new = (t_list *)malloc(sizeof(t_list));
		new_str = ft_strjoin(str, old_pwd);
		new->value = new_str;
		new->next = NULL;
		ft_lstadd_front(saving_env, new);
	}
}
void	modify_Pwd(t_list **saving_env, char *new_pwd)
{
	t_list	*pwd_found;
	
	pwd_found = search_Pwd(*saving_env);
	pwd_found->value = ft_strjoin("PWD=", new_pwd);
	
}

// void	export(char **p, )
// {
	
// }

void	execution(t_args *p, char **env)
{
	int		i;
    // char	*line;
    // char	**p;
	t_list	*saving_env;
	t_list	*data;
	t_list	*tmp;
	t_list	*tmp1;
	t_list	*saving_expo;
	// t_list	*saving_expo;

	data = (t_list *)malloc(sizeof(t_list));
	saving_env = get_env(env);
	saving_expo = get_env(env);
	char	*find_path;
	// while (1)
    // {
    //     line = readline("minishell$ ");
	// 	add_history(line);
	// 	if (!line)
	// 		exit (1);
	// 	p = ft_split(line, ' ');
		if (!ft_strcmp(p->args[0], "echo"))
			echo(p->args);
		else if (!ft_strcmp(p->args[0], "pwd"))
		{
			char filename[256];
			getcwd(filename, 256);
			printf("%s\n", filename);
		}
		else if (!ft_strcmp(p->args[0], "cd"))
		{
			char old_pwd[256];
			char new_pwd[256];
			getcwd(old_pwd, 256);
			if (cd(p->args, saving_expo) == 1)
			{
				getcwd(new_pwd, 256);
				add_OldPwd(&saving_env, old_pwd);							//////////////come back
				modify_Pwd(&saving_env, new_pwd);
				add_OldPwd(&saving_expo, old_pwd);							//////////////come back
				modify_Pwd(&saving_expo, new_pwd);
			}
		}
		else if (!ft_strcmp(p->args[0], "env"))
		{
			tmp = saving_env;
			while (saving_env)
			{
				printf("%s\n", saving_env->value);
				saving_env = saving_env->next;
			}
			saving_env = tmp;
		}
		else if (!ft_strcmp(p->args[0], "unset"))
		{
			i = 1;
			while (p->args[i])
			{
				unset(&saving_expo, p->args[i]);
				unset(&saving_env, p->args[i]);
				i++;
			}
		}
		else if (!ft_strcmp(p->args[0], "exit"))
		{
			i = 1;
			if (p->args[i])
			{
				int return_value;
				return_value = ft_atoi(p->args[i]);
				exit(return_value);
			}
			else
				exit (0);
		}
		else if (!ft_strcmp(p->args[0], "export"))
		{
			t_list	*node;
			int x = 0;
			
			i = 1;
			if (p->args[i])
			{
				while (p->args[i])
				{
					x = 0;
					while (p->args[i][x])
					{
						if(p->args[i][x] == '+' && p->args[i][x + 1] == '=')
						{
							char **spl_p;
							spl_p = ft_split(p->args[i], '=');
							node = search_node(saving_expo, spl_p[0]);
							char *res;
							res = ft_strjoin(node->value, spl_p[1]);
						}
						else if (p->args[i][x] == '=' && x > 0)
						{
							saving_env = export(p->args[i], &saving_env);
							break ;
						}
						x++;
					}
					saving_expo = export(p->args[i], &saving_expo);
					i++;
				}
			}
			else
			{
				if (saving_expo)
				{
					saving_expo = sort_list(&saving_expo);
					tmp1 = saving_expo;
					while (saving_expo)
					{
						printf("%s\n", saving_expo->value);
						saving_expo = saving_expo->next;
					}
					saving_expo = tmp1;
				}
			}
		}
		else
		{
			char	**spl_path;
			char	*command;
			char	*cmd;

			find_path = search_path(saving_expo, "PATH");
			// printf("%s\n", find_path);
			spl_path = ft_split(find_path, ':');
			cmd = ft_strjoin("/", p->args[0]);
			i = 0;
			while (spl_path[i])
			{
				command = ft_strjoin(spl_path[i], cmd);
				if (access(command, X_OK) != -1)
					execve(command, &p->args[0], NULL);
				i++;
			}
			exit(0);
		}
}
