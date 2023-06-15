/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:48:28 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/14 22:51:46 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	split_args2_follow(t_token *temp, t_token *lst, t_args **args)
// {
	
// }

int split_args2(t_token *temp, t_args **args, t_token *lst, t_env *env_parse)
{
    int		x;
	int		y;
    int     in;
    int     out;

	in = 0;
	out = 0;
    while (temp && *args)
	{
        if (temp->type == INPUT || temp->type == OUTPUT || temp->type == APPEND)
        {
            if (split_args3(temp, args, &in, &out))
                return (1);
            temp = temp->next;
        }
		else if ((temp->type == CMD || temp->type == PIPE) && temp->data[0])
		{
			if (temp->type == PIPE)
			{
				x = 0;
				y = 0;
				*args = (*args)->next;
			}
			else
			{
				if (!x)
				{
					x = args_count(lst);
					(*args)->args = malloc(sizeof(char *) * (x + 1));
					(*args)->args[x] = NULL;
				}
				(*args)->args[y] = ft_strdup(temp->data);
				y++;
			}
		}
		else if (temp->type == DELIMITER)
		{
			if (heredoc(*args, temp->data, env_parse, lst))
				return (1);
		}
		check_in_out(*args, in, out);
		free (temp->data);
		temp = temp->next;
	}
    return (0);
}