/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:53:36 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/14 23:01:28 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	split_args3_follow(t_token *temp, t_args **args, int *out)
{
	*out = 1;
	if ((*args)->outfile == -1)
	{
		perror(temp->next->data);
		return (1);
	}
	return (0);
}

int	split_args3(t_token *temp, t_args **args, int *in, int *out)
{
	if (temp->next && temp->type == INPUT)
	{
		*in = 1;
		(*args)->infile = open(temp->next->data, O_RDWR);
		if ((*args)->infile == -1)
		{
			perror(temp->next->data);
			return (1);
		}
	}
	else if (temp->next && temp->type == OUTPUT)
	{
		(*args)->outfile = open(temp->next->data,
				O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (split_args3_follow(temp, args, out))
			return (1);
	}
	else if (temp->next && temp->type == APPEND)
	{
		(*args)->outfile = open(temp->next->data,
				O_RDWR | O_CREAT | O_APPEND, 0777);
		if (split_args3_follow(temp, args, out))
			return (1);
	}
	return (0);
}
