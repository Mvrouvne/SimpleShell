/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:23:27 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/11 08:40:40 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	[]
	echo "\n"
	echo -n ""
	function checkArgs(char **p, int *flag)
	{
		*flag = 1;
		*flag = 0;
		
	}
*/


// int	parseArg(char **p)
// {
// 	int i = 0;
// 	int count = 0;
// 	while (p[i])
// 	{
// 		if (!strncmp(p[i], "-n", 2))
// 			count++;
// 		else if (count > 0 || i == 1)
// 			break;
// 		i++;
// 	}
// 	return count;
// }

// void ft_echo(char **p)
// {
// 	int count = parseArg(p);
// 	int flag = count;
// 	count++;
// 	while (p[count])
// 	{
// 		write(1, p[count], strlen(p[count]));
// 		if (p[count + 1])
// 			write(1, " ", 1);
// 		count++;
// 	}
// 	if (flag == 0)
// 		write(1, "\n", 1);
// }

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

int	cd(char **p)
{
	if (!ft_strcmp(p[1], "~"))
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

	cur = (*head);
	prev = NULL;
	
	//search for the node in my lincked list
	while(cur != NULL && cur->next != NULL && ft_strncmp(cur->value, key, ft_strlen(key)))
	{
		prev = cur;
		cur = cur->next;
	}
	//if the node we re looking for is the first node///that means prev still have NULL value
	if (prev == NULL)
		(*head) = cur->next;
	//if the node we re locking for is in the middle or in the end///that means the prev node is before the cur node
	else
		prev->next = cur->next;
	free (cur);
}

void	add_OldPwd(t_list **saving_env, char *old_pwd)
{
	t_list	*new;
	(void) saving_env;
	char	str[8] = "OLDPWD=";
	int		i;
	char	*new_str;
	
	i = ft_strlen(old_pwd) + ft_strlen(str) + 1;
	new = (t_list *)malloc(sizeof(t_list));
	new_str = ft_strjoin(str, old_pwd);
	new->value = new_str;
	new->next = NULL;
	// ft_lstadd_front(saving_env, new);
}

int main(int ac, char **av, char **env)
{
	(void)	ac;
	(void)	av;
    char	*line;
    char	**p;
	t_list	*saving_env;
	t_list	*data;
	t_list	*tmp;

	data = (t_list *)malloc(sizeof(t_list));
	saving_env = get_env(env);
	
    while (1)
    {
        line = readline("minishell$ ");
		add_history(line);
		if (!line)
			exit (1);
		p = ft_split(line, ' ');
		if (!ft_strcmp(p[0], "echo"))
			echo(p);
		 if (!ft_strcmp(p[0], "pwd"))
		{
			char filename[256];
			getcwd(filename, 256);
			printf("%s\n", filename);
		}
		else if (!ft_strcmp(p[0] , "exit"))
			exit(0);
		else if (!ft_strcmp(p[0], "env"))
		{
			tmp = saving_env;
			while (saving_env)
			{
				printf("%s\n", saving_env->value);
				saving_env = saving_env->next;
			}
			saving_env = tmp;
		}
		else if (!ft_strcmp(p[0], "cd"))
		{
			char old_pwd[256];
			getcwd(old_pwd, 256);
			if (cd(p) == 1)
				add_OldPwd(&saving_env, old_pwd);
		}
		else if (!ft_strcmp(p[0], "unset"))
		{
			unset(&saving_env, p[1]);
		}
	}
}