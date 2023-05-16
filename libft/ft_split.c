/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:20:20 by otitebah          #+#    #+#             */
/*   Updated: 2022/11/03 22:12:06 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i ++;
	}
	free(p);
	return (0);
}

static char	**alloc(const char *s, char c)
{
	int		count;
	int		i;
	int		test;
	char	**p;

	count = 0;
	i = 0;
	test = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && test == 0)
		{
			count ++;
			test = 1;
		}
		if (s[i] == c)
			test = 0;
		i++ ;
	}
	p = (char **)malloc(sizeof(char *) * (count + 1));
	if (!p)
		return (0);
	return (p);
}

static char	**mini_split(char const *s, char c, char **m)
{
	size_t	i;
	int		start;
	int		k;

	k = 0;
	i = 0;
	start = -1;
	if (!m)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start == -1)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			m[k++] = ft_substr(s, start, (i - start));
			if (!m[k - 1])
				return (ft_free(m));
			start = -1;
		}
		i++;
	}
	m[k] = NULL;
	return (m);
}

char	**ft_split(char const *s, char c)
{
	char	**m;
	char	**x;

	x = alloc (s, c);
	if (!x)
		return (0);
	m = mini_split (s, c, x);
	if (!m)
		return (0);
	return (m);
}
