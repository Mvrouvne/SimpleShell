/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:26:11 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/17 16:25:55 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*a;
	char	o;
	int		b;

	o = (char )c;
	a = (char *)s;
	b = ft_strlen(a);
	i = 0;
	if (o == '\0')
		return (&a[b]);
	while (a[i])
	{
		if (a[i] == o)
		{
			return (a + (i + 1));
		}
		i++;
	}
	return (0);
}
