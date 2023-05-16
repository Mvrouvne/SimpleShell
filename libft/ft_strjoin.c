/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:37:21 by otitebah          #+#    #+#             */
/*   Updated: 2022/11/05 15:22:31 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*m;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	m = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!m)
		return (NULL);
	while (s1[i])
	{
		m[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		m[i + j] = s2[j];
		j++;
	}
	m[i + j] = '\0';
	return (m);
}
