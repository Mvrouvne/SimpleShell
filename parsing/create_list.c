#include "minishell.h"

int	create_list(t_args **args, t_token **token)
{
	t_token *temp;

	temp = *token;
	ft_lstadd_back2(args, ft_lstnew3());
	while (temp)
	{
		if (temp->type == PIPE)
			ft_lstadd_back2(args, ft_lstnew2());
		temp = temp->next;
	}
	return (0);
}
