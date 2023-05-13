#include "minishell.h"

int	create_list(t_args **args, t_token *token)
{
	ft_lstadd_back2(args, ft_lstnew2());
	while (token)
	{
		if (token->type == PIPE)
			ft_lstadd_back2(args, ft_lstnew2());
		token = token->next;
	}
	return (0);
}
