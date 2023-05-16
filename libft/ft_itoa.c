/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:42:56 by otitebah          #+#    #+#             */
/*   Updated: 2022/11/05 15:29:44 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_len(long nb)
{
	long	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		len ++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*m;
	int		len;
	long	var;

	var = n;
	len = ft_len(var);
	m = malloc(sizeof(char) * len + 1);
	if (!m)
		return (NULL);
	m[len] = '\0';
	if (var == 0)
		m[0] = '0';
	if (n < 0)
	{
		var = var * -1;
		m[0] = '-';
	}
	while (var)
	{
		m[--len] = var % 10 + '0';
		var = var / 10;
	}
	return (m);
}
