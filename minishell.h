/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:13:07 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/23 04:10:20 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef	MINISHELL_H
# define	MINISHELL_H

#include "parsing/parsing.h"
#include "execution/execution.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_global
{
    char	*line;
	t_token	*lst;
	t_args	*args;
	t_args	*tmp;
	int		x;
	t_data *list;
	t_pipe	*pipes;
	t_env	*env_parse;
	char **env_copy;
}   t_global;

# endif