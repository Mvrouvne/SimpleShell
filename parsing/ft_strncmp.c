/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:16:49 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/14 22:24:59 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			x;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	x = 0;
	while ((x < n) && (cs1[x] != '\0' || cs2[x] != '\0'))
	{
		if (cs1[x] > cs2[x])
		{
			return (1);
		}
		else if (cs1[x] < cs2[x])
		{
			return (-1);
		}
		x++;
	}
	return (0);
}
