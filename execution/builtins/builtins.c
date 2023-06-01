/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:23:27 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/31 07:12:19 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	check_n(char *str)
{
	int	i;

	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);    //hai ila lqa dik -n olqa mlassqa meaha chi haja mn ghir n
			i++;
		}
		return (0);// hadi ila dak arg fih gha "-nnnnn"
	}
	return (2);// hadi ila aslan makinach -n yaeni khasso ykteb dakchi kaml li bead mnha
}

void	echo(char **p)
{
		int	i;

	i = 1;
	if (p[i] == NULL)
	{
		printf("\n");
		return ;
	}
	while (p[i])
	{
		if (check_n(p[i]) == 1)
		{
			while (p[i])
				printf("%s ", p[i++]);
			if (check_n(p[1]) == 1)
				printf("\n");
			return ;
		}
		else if (check_n(p[i]) == 2)
		{
			while (p[i])
				printf("%s ", p[i++]);
			printf("\n");
			return;
		}
		else if (check_n(p[i]) == 2)
		{
			while (p[i])
			{
				printf("%s ", p[i++]);
			}
			return ;
		}
		i++;
	}
	if (check_n(p[1]) == 2)
		printf("ta sir\n");
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


// void	export(char **p, )
// {
	
// }

void	execution(t_args **p, t_list **saving_env, t_list **saving_expo, char **env)
{
	int		i;
	t_list	*data;
	t_list	*tmp;

	data = (t_list *)malloc(sizeof(t_list));
		if (!ft_strcmp((*p)->args[0], "echo"))					//<----- {  echo  }
			echo((*p)->args);
		else if (!ft_strcmp((*p)->args[0], "pwd"))				//<----- {  pwd  }
		{
			char filename[256];
			getcwd(filename, 256);
			printf("%s\n", filename);
		}
		else if (!ft_strcmp((*p)->args[0], "cd"))				//<----- {  cd  }
			big_cd(&(*saving_env), &(*saving_expo), p);
		else if (!ft_strcmp((*p)->args[0], "env"))				//<----- {  env  }
		{
			tmp = (*saving_env);
			while (*saving_env)
			{
				printf("%s\n", (*saving_env)->value);
				(*saving_env) = (*saving_env)->next;
			}
			(*saving_env) = tmp;
		}
		else if (!ft_strcmp((*p)->args[0], "unset"))			//<----- {  unset  }
		{
			i = 1;
			while ((*p)->args[i])
			{
				unset(saving_expo, (*p)->args[i]);
				unset(saving_env, (*p)->args[i]);
				i++;
			}
		}
		else if (!ft_strcmp((*p)->args[0], "exit"))				//<----- {  exit  }
		{
			i = 1;
			if ((*p)->args[i])
			{
				int return_value;
				return_value = ft_atoi((*p)->args[i]);
				exit(return_value);
			}
			else
				exit (0);
		}
		else if (!ft_strcmp((*p)->args[0], "export"))			//<----- {  export  }
			export_a(saving_expo, saving_env, p);
		else
		{
			Implement_Cmnd((*saving_expo), *p, env);
		}
}
