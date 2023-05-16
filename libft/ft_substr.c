/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:00:12 by otitebah          #+#    #+#             */
/*   Updated: 2022/11/04 17:41:17 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*m;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	i = 0;
	m = malloc(sizeof(char) * (len + 1));
	if (!m)
		return (NULL);
	if (s[0] == '\0')
		return (0);
	while (i < len && s[i + start] && start < ft_strlen(s))
	{
		m[i] = s[i + start];
		i++;
	}
	m[i] = '\0';
	return (m);
}
