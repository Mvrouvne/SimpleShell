#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			x;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	x = 0;
	while (cs1[x] != '\0' || cs2[x] != '\0')
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