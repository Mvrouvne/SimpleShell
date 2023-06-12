/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:14:32 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/12 23:18:55 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_chrjoin(char *s1, char c2)
{
	int		x;
	int		y;
	char	*join;

	if (!s1)
		return (ft_strdup(&c2));
	join = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!join)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[x])
	{
		join[x] = s1[x];
		x++;
	}
    join[x] = c2;
	join[x + 1] = '\0';
	free (s1);
	return (join);
}

