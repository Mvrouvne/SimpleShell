/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:53:36 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/19 13:06:11 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	split_args3_follow2(t_token *temp, t_args **args, int *in)
{
	extern int	g_exit_status;

	*in = 1;
	if ((*args)->infile == -1)
	{
		perror(temp->next->data);
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (0);
}

int	split_args3_follow(t_token *temp, t_args **args, int *out)
{
	extern int	g_exit_status;

	*out = 1;
	if ((*args)->outfile == -1)
	{
		perror(temp->next->data);
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (0);
}

int	split_args3(t_token *temp, t_args **args, int *in, int *out)
{
	extern int	g_exit_status;

	if (temp->next && temp->type == INPUT)
	{
		(*args)->infile = open(temp->next->data, O_RDWR);
		if (split_args3_follow2(temp, args, in))
			return (g_exit_status);
	}
	else if (temp->next && temp->type == OUTPUT)
	{
		(*args)->outfile = open(temp->next->data,
				O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (split_args3_follow(temp, args, out))
			return (g_exit_status);
	}
	else if (temp->next && temp->type == APPEND)
	{
		(*args)->outfile = open(temp->next->data,
				O_RDWR | O_CREAT | O_APPEND, 0777);
		if (split_args3_follow(temp, args, out))
			return (g_exit_status);
	}
	return (0);
}
