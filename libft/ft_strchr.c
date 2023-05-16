/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:26:11 by otitebah          #+#    #+#             */
/*   Updated: 2022/10/27 12:14:58 by otitebah         ###   ########.fr       */
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
			return (a + i);
		}
		i++;
	}
	return (0);
}
