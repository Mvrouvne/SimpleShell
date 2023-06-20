/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:13:57 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/20 14:08:48 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list	*search_node(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node) - 1)) == 0)
		{
            puts("node");
			printf("tmp :%s\n", tmp->value);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int search_node_1(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node) - 1)) == 0)
		{
            puts("node");
			printf("tmp :%s\n", tmp->value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

// int plus_condition(t_list **saving_env, t_list *node, char *p, char **spl_p)
// {
// 	char **Remove_Plus;
// 	char *join;
// 	char *res;
// 	char *res1;
// 	if (node)
// 	{	
// 		res = ft_strjoin(node->value, spl_p[1]);
// 		res1 = ft_strjoin(node2->value, spl_p[1]);
// 		node->value = res;
// 		node2->value = res1;
// 		return ;
// 	}
// 	else
// 	{
// 		Remove_Plus = ft_split(p, '+');
// 		join = ft_strjoin(Remove_Plus[0], Remove_Plus[1]);
// 		(*saving_env) = export(join, &(*saving_env));
// 		return ;
// 	}
// }

void    export_a(t_list **saving_env, t_list **saving_expo, t_args *p)
{
    t_list	*node = NULL;
    t_list	*node2 = NULL;
	t_list	*tmp1;
    char **spl_p = NULL;
    int     x;
    int     i;
    (void)saving_env;
    
    x = 0;
    i = 1;
    if (p->args[i])
    {
        while (p->args[i])
        {
        //     x = 0;
        //     // system("leaks minishell");
        //     while (p->args[i][x])
        //     {
                if((p->args[i][0] < 'a' || p->args[i][0] > 'z')
                    && (p->args[i][0] < 'A' || p->args[i][0] > 'Z'))
                {
                    ft_error("minishell: ", p->args[i], "not a valid identifier", 1);
                    return ;
                }
               if(search_plus(p->args[i]) == 2)
                {
                    // char **spl_p;
                    spl_p = ft_split(p->args[i], '=');
                    node = search_node((*saving_expo), spl_p[0]);
                    node2 = search_node((*saving_env), spl_p[0]);
                    if (node)
                    {	
                        if (search_egal(node->value) == 0)
                        {
                            puts("++++++");
                            char *str;
                            char *rslt;
                            str = ft_strjoin(spl_p[0], "=");
                            rslt = ft_strjoin(str, spl_p[1]);
                            node->value = rslt;
                            node2->value = rslt;
                            return ;
                        }
                        puts("---------");
                        char *res;
                        char *res1;
                        res = ft_strjoin(node->value, spl_p[1]);
                        res1 = ft_strjoin(node2->value, spl_p[1]);
                        node->value = res;
                        node2->value = res1;
                        return ;
                    }
                    else
                    {
                        puts("*******");
                        char **Remove_Plus;
                        char *join;
                        Remove_Plus = ft_split(p->args[i], '+');
                        join = ft_strjoin(Remove_Plus[0], Remove_Plus[1]);
                        puts(join);
                        (*saving_env) = export(join, &(*saving_env));
                        (*saving_expo) = export(join, &(*saving_expo));
                        // return ;
                    }
                }
                else if (search_egal(p->args[i]) == 1)
                {
                    env_if_egal(p->args[i], &(*saving_env));
                    (*saving_expo) = export(p->args[i], &(*saving_expo));
                    // return ;
                }
                // else if(search_egal(p->args[i]) == 0)
                // {
                //     node = search_node((*saving_expo), p->args[i]);
                //     if(node)
                //     {
                //         char *ress;
                //         ress = ft_strjoin
                //     }
                // }
                else
                {
                    (*saving_expo) = export(p->args[i], saving_expo);
                    // return ;
                }
        //         x++;
        //     }
        //     puts("hana");
            i++;
        //     // free(node);
        //     // free(node2);
        //     // ft_free(spl_p);
        }
    }
    else
    {
        if (*saving_expo)
        {
            char **sp = NULL;
            char *add_quotes = NULL;
            char *add_quotes2 = NULL;
            char *final = NULL;
            char *add_egal = NULL;
            (*saving_expo) = sort_list(saving_expo);
            tmp1 = (*saving_expo);
            while ((*saving_expo))
            {
                if (search_egal((*saving_expo)->value) == 1)
                {
                    sp = ft_split((*saving_expo)->value, '=');
                    if (sp[1])
                    {
                        add_quotes = ft_strjoin("\"", sp[1]);
                        add_quotes2 = ft_strjoin(add_quotes, "\"");
                        add_egal = ft_strjoin("=", add_quotes2);
                        final = ft_strjoin(sp[0], add_egal);
                        free(add_quotes);
                        free(add_quotes2);
                        free(add_egal);
                    }
                    else
                    {
                        final = (*saving_expo)->value;
                        // final = ft_strjoin((*saving_expo)->value, "\"");
                        // free(final);
                    }
					ft_free(sp);
                }
                else
                    final = (*saving_expo)->value;
                ft_putstr_fd("declare -x  ", 1);
                ft_putendl_fd(final, 1);
                // free(final);
                (*saving_expo) = (*saving_expo)->next;
                // free(final);
            }
            (*saving_expo) = tmp1;
        }
    }
}

void    ft_error(char *entourage, char *input, char *error, int i)
{
    ft_putstr_fd(entourage, i);
    ft_putstr_fd(input, i);
    ft_putstr_fd(": ", i);
    ft_putendl_fd(error, i);
}

void	ft_free(char **str)
{
	int		i;

	i = 0;
    if (!str)
        return ;
	while (str[i])
		free(str[i++]);
	free(str);
}