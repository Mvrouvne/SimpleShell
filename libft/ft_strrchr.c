/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:38:09 by otitebah          #+#    #+#             */
/*   Updated: 2022/10/27 13:57:32 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*a;
	char	o;
	int		s;

	a = (char *)str;
	o = (char )c;
	s = ft_strlen(a);
	if (o == '\0')
		return (&a[s]);
	i = ft_strlen(a) - 1;
	while (i >= 0)
	{
		if (a[i] == o)
			return (a + i);
		i--;
	}
	return (NULL);
}
