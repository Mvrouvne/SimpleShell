#include "parsing.h"

int	errors_check(t_token *lst)
{
	int	x;

	x = 0;
	if ((!(lst->next)) && ((!(ft_strcmp(lst->data, "<"))) || (!(ft_strcmp(lst->data, "<<")))
		|| (!(ft_strcmp(lst->data, ">")) || (!(ft_strcmp(lst->data, ">>"))))))
	{
		write (2, "bash: syntax error near unexpected token `newline'\n", 52);
		exit (258);
	}
	else if (!(ft_strcmp(lst->data, "<")))
	{
		if (lst->next && (!(ft_strcmp(lst->next->data, "|"))))
		{
			write (2, "bash: syntax error near unexpected token `|'\n", 45);
			exit (258);
		}
	}
	// while (lst)
	// {
	// }
	return (0);
}