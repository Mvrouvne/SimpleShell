/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:09:11 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/17 21:54:18 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int split_args3(t_token *temp, t_args **args, int *in, int *out)
// {
//     if (temp->next && temp->type == INPUT)
// 	{
// 		*in = 1;
// 		(*args)->infile = open(temp->next->data, O_RDWR);
// 		if ((*args)->infile == -1)
// 		{
// 			perror(temp->next->data);
// 			return (1);
// 		}
// 	}
// 	else if (temp->next && temp->type == OUTPUT)
// 	{
// 		*out = 1;
// 		(*args)->outfile = open(temp->next->data, O_RDWR | O_CREAT | O_TRUNC, 0777);
// 		if ((*args)->outfile == -1)
// 		{
// 			perror(temp->next->data);
// 			return (1);
// 		}
// 	}
// 	else if (temp->next && temp->type == APPEND)
// 	{
// 		*out = 2;
// 		(*args)->outfile = open(temp->next->data, O_RDWR | O_CREAT | O_APPEND, 0777);
// 		if ((*args)->outfile == -1)
// 		{
// 			perror(temp->next->data);
// 			return (1);
// 		}
// 	}
//     return (0);
// }

// int split_args2(t_token *temp, t_args **args, t_token *lst, t_env *env_parse)
// {
//     int		x;
// 	int		y;
// 	int		z;
//     int     in;
//     int     out;

// 	y = 0;
// 	z = 0;
// 	in = 0;
// 	out = 0;
//     while (temp && *args)
// 	{
//         if (temp->type == INPUT || temp->type == OUTPUT || temp->type == APPEND)
//         {
//             if (split_args3(temp, args, &in, &out))
//                 return (1);
//             temp = temp->next;
//         }
// 		else if ((temp->type == CMD || temp->type == PIPE) && temp->data[0])
// 		{
// 			if (temp->type == PIPE)
// 			{
// 				y = 0;
// 				*args = (*args)->next;
// 				x = 0;
// 				z = 0;
// 				x = args_count(lst);
// 				(*args)->args = malloc(sizeof(char *) * (x + 1));
// 				z++;
// 				(*args)->args[x] = NULL;
// 			}
// 			else
// 			{
// 				if (!y && !z)
// 				{
// 					x = 0;
// 					x = args_count(lst);
// 					(*args)->args = malloc(sizeof(char *) * (x + 1));
// 					(*args)->args[x] = NULL;
// 				}
// 				(*args)->args[y] = ft_strdup(temp->data);
// 				y++;
// 			}
// 			check_in_out(*args, in, out);
// 		}
// 		else if (temp->type == DELIMITER)
// 		{
// 			if (heredoc(*args, temp->data, env_parse, lst))
// 				return (1);
// 			// wait(NULL);
// 		}
// 		free (temp->data);
// 		temp = temp->next;
// 	}
//     return (0);
// }

int	split_args(t_token *lst, t_args **args, t_env *env_parse)
{
	t_token	*temp;
	t_args	*temp2;
	int		max;

	max = 0;
	t_token *tmp = lst;
	while (tmp)
	{
		if (tmp->av_quotes != 1)
			tmp->av_quotes = 0;
		if (!(ft_strcmp(tmp->data, "<<")))
			max++;
		tmp = tmp->next;
	}
	if (max >= 16)
	{
		write (2, "maximum here-document count exceeded\n", 38);
		return (1);
	}
	temp = lst;
	create_list(args, lst);
	(*args)->args = malloc(sizeof(char *));
	(*args)->args[0] = NULL;
	// printf("args 0 adress = %p\n", (*args)->args);
	temp2 = *args;
    if (split_args2(temp, args, lst, env_parse))
        return (1);
	*args = temp2;
	return (0);
}
