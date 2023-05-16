#include "parsing.h"

// char	*ft_strchr(char *str, int c)
// {
// 	size_t	x;
// 	size_t	len;

// 	x = 0;
// 	len = ft_strlen(str);
// 	while (x <= len)
// 	{
// 		if (str[x] == (char)c)
// 			return ((char *) &str[++x]);
// 		x++;
// 	}
// 	return (0);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		x;
// 	int		y;
// 	char	*join;

// 	if (!s1)
// 		return (ft_strdup(s2));
// 	join = malloc(sizeof(char) * (ft_strlen(s2) + ft_strlen(s1) + 1));
// 	if (!join)
// 		return (NULL);
// 	x = 0;
// 	y = 0;
// 	while (s1[x])
// 	{
// 		join[x] = s1[x];
// 		x++;
// 	}
// 	while (s2[y])
// 	{
// 		join[x] = s2[y];
// 		y++;
// 		x++;
// 	}
// 	join[x] = '\0';
// 	// free (s1);
// 	return (join);
// }

// char	*ft_strdup(const char *s1)
// {
// 	char	*p;
// 	int		len;
// 	int		x;

// 	len = ft_strlen(s1);
// 	p = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!p)
// 		return (NULL);
// 	x = 0;
// 	while (s1[x] != '\0')
// 	{
// 		p[x] = s1[x];
// 		x++;
// 	}
// 	p[x] = '\0';
// 	return (p);
// }
