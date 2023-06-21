/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:48:28 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/20 16:41:24 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	split_args2_follow2(t_token *temp, t_args **args, int *y)
{
	int	z;
	int	x;

	*y = 0;
	*args = (*args)->next;
	x = 0;
	z = 0;
	x = args_count(temp->next);
	(*args)->args = malloc(sizeof(char *) * (x + 1));
	(*args)->args[x] = NULL;
	z++;
	return (z);
}

int	split_args2_follow(t_token *temp, t_args **args, int y, int z)
{
	int	x;

	x = 0;
	if (!y && !z)
	{
		x = args_count(temp);
		free ((*args)->args);
		(*args)->args = malloc(sizeof(char *) * (x + 1));
		(*args)->args[x] = NULL;
	}
	return (x);
}

int split_args2(t_token *temp, t_args **args, t_token *lst, t_env *env_parse)
{
    int		x;
	int		y;
	int		z;
    int     in;
    int     out;

	x = 0;
	y = 0;
	z = 0;
	in = 0;
	out = 0;
    while (temp && *args)
	{
        if (temp->type == INPUT || temp->type == OUTPUT || temp->type == APPEND)
        {
            if (split_args3(temp, args, &in, &out))
                return (free (temp->data), free (temp->next->data), 1);
			free (temp->data);
            temp = temp->next;
        }
		else if ((temp->type == CMD || temp->type == PIPE))
		{
			if (temp->type == PIPE)
				z = split_args2_follow2(temp, args, &y);
			else
			{
				x = split_args2_follow(temp, args, y, z);
				(*args)->args[y++] = ft_strdup(temp->data);
			}
		}
		else if (temp->type == DELIMITER)
		{
			in = 1;
			if (heredoc(*args, temp->data, env_parse, lst))
				return (free (temp->data), 1);
		}
		check_in_out(*args, in, out);
		free (temp->data);
		temp = temp->next;
	}
    return (0);
}
