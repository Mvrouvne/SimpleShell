/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:56:27 by otitebah          #+#    #+#             */
/*   Updated: 2022/11/05 15:46:10 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	findset(char c, char const *s1)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (c == s1[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	bdya;
	size_t	lkhr;
	size_t	i;
	char	*m;

	bdya = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	while (s1[bdya] && findset(s1[bdya], set))
		bdya++;
	lkhr = ft_strlen(s1);
	while (lkhr > bdya && findset(s1[lkhr - 1], set))
		lkhr--;
	m = malloc(sizeof(char) * (lkhr - bdya) + 1);
	if (!m)
		return (NULL);
	i = 0;
	while (bdya < lkhr)
	{
		m[i] = s1[bdya];
		i++;
		bdya++;
	}
	m[i] = '\0';
	return (m);
}
