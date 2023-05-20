#include "parsing.h"

int	expanded_quotes(t_token **lst, char *str, char *line, int *x)
{
	char	*expanded;
	int		y;

	y = 0;
	while (str[y])
	{
		if (str[y] == '"')
		{
			y++;
			while (str[y] != '"')
			{
				expanded = ft_chrjoin(expanded, str[y]);
				y++;
			}
		}
		else if (str[y] == '\'')
		{
			y++;
			while (str[y] != '\'')
			{
				expanded = ft_chrjoin(expanded, str[y]);
				y++;
			}
		}
		else 
			expanded = ft_chrjoin(expanded, str[y]);
		y++;
	}
	while (line[*x] != ' ')
		(*x)++;
	printf("expanded = %s\n", expanded);
	if (expanded)
		ft_lstadd_back(lst, ft_lstnew(expanded));
	return (0);
}