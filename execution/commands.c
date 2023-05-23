/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:07:16 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/23 17:05:00 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*search_path(t_list *saving_expo, char *node)
{
	t_list	*tmp;
	char **spl;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node))) == 0)
		{
			spl = ft_split(tmp->value, '=');
			// printf("PATH ---> [** %s **]\n", spl[1]);
			return (spl[1]);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	Implement_Cmnd(t_list *saving_expo, t_args *p, char **env)
{
	char	**spl_path;
	char	*command;
	char	*cmd;
	char	*find_path;
	int		i;
	int		fd;
	(void)env;

	find_path = search_path(saving_expo, "PATH");
	// printf("%s\n", find_path);
	spl_path = ft_split(find_path, ':');
	cmd = ft_strjoin("/", p->args[0]);
	i = 0;
	fd = fork();
	if (fd == 0)
	{
		while (spl_path[i])
		{
			command = ft_strjoin(spl_path[i], cmd);
			if (access(command, X_OK) != -1)
				execve(command, &p->args[0], env);
			i++;
		}
		close (fd);
	}
	wait(NULL);
}