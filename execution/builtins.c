/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:23:27 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/07 12:51:00 by otitebah         ###   ########.fr       */
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
// void	echo(char **p)
// {
// 	int	i;
// 	int	x;
// 	int	y;
	
// 	i = 1;
// 	while(p[i]) //count how much args i have
// 		i++;
// 	y = i;
// 	i = 1;
// 	while (p[i])
// 	{
// 		printf("=== %s\n", p[i]);
// 		x = 2;
// 		while (!ft_strncmp(p[i], "-n", ft_strlen("-n")) && y > 2)
// 		{
// 			x = 2;
// 			while (p[i][x])
// 			{
// 				if (p[i][x] != 'n')
// 				{
// 					printf("%s ", p[i]);
// 					break ;
// 				}
// 				x++;
// 			}
// 			i++;
// 		}
// 		printf ("%s ", p[i]);
// 		i++;
// 	}
// 	if (ft_strncmp(p[1], "-n", ft_strlen("-n"))) 
// 		printf("\n");
// }

void	cd(char **p)
{
	if (!ft_strcmp(p[1], "~"))
		chdir(getenv("HOME"));
	else if (chdir(p[1]))
		perror("minishell: cd");
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

int main(int ac, char **av, char **env)
{
	(void)	ac;
	(void)	av;
	(void)	env;
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
		if (!line)
			exit (1);
		p = ft_split(line, ' ');
		// if (!ft_strcmp(p[0], "echo"))
		// 	ft_echo(p);
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
			cd(p);
		else if (!ft_strcmp(p[0], "unset"))
		{
			unset(&saving_env, p[1]);
		}
	}
}