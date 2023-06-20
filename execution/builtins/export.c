/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:13:57 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/20 22:34:48 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list	*search_node(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node))) == 0)
		{
            puts("node");
			printf("tmp :%s\n", tmp->value);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_list	*search_node1(t_list *saving_expo, char *node)
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
            if((p->args[i][0] < 'a' || p->args[i][0] > 'z')
                && (p->args[i][0] < 'A' || p->args[i][0] > 'Z'))
            {
                ft_error("minishell: ", p->args[i], "not a valid identifier", 1);
                return ;
            }
            else if (search_plus(p->args[i]) == 0 && search_egal(p->args[i]) == 0
                    && !search_node(*saving_expo, p->args[i]))
                (*saving_expo) = export(p->args[i], &(*saving_expo));
            else if (search_egal(p->args[i]) == 3)
            {
                (*saving_env) = export(p->args[i], &(*saving_env));
                (*saving_expo) = export(p->args[i], &(*saving_expo));
            }
            else if (search_egal(p->args[i]) == 1 && search_plus(p->args[i]) == 0)
            {
                puts("kayna '=' o makinach '+'");
                spl_p = ft_split(p->args[i], '=');
                node = search_node(*saving_expo, spl_p[0]);
                node2 = search_node(*saving_env, spl_p[0]);
                if (node)
                {
                    puts("true");
                    puts(node->value);
                    char *str;
                    char *res;
                    str = ft_strjoin(spl_p[0], "=");
                    res = ft_strjoin(str, spl_p[1]);
                    free(node2->value);
                    free(node->value);
                    node2->value = ft_strdup(res);
                    node->value = ft_strdup(res);
                }
                else
                    (*saving_env) = export(p->args[i], &(*saving_env));
                    (*saving_expo) = export(p->args[i], &(*saving_expo));
                ft_free(spl_p);
            }
            else if (search_plus(p->args[i]) == 2)
            {
                    puts("there is +");
                    char    **spl;
                    spl = ft_split(p->args[i], '=');
                    spl_p = ft_split(p->args[i], '+');
                    if(!search_node_1(*saving_expo, spl_p[0]))
                    {
                        puts("remove plus");
                        char **remove_plus;
                        char *res;
                        remove_plus = ft_split(p->args[i], '+');
                        res = ft_strjoin(remove_plus[0], remove_plus[1]);
                        (*saving_expo) = export(res, &(*saving_expo));
                        (*saving_env) = export(res, &(*saving_env));
                    }
                    else if (search_node(*saving_expo, spl_p[0]))
                    {
                        puts("true");
                        node = search_node(*saving_expo, spl_p[0]);
                        node2 = search_node1(*saving_env, spl[0]);
                        char *res;
                        char *final;
                        char *add_egal;
                        char **old_value;
                        old_value = ft_split(node->value, '=');
                        add_egal = ft_strjoin(old_value[0], "=");
                        if (old_value[1])
                        {
                            res = ft_strjoin(add_egal, old_value[1]);
                            final = ft_strjoin(res, spl[1]);
                        }
                        else
                        {
                            final = ft_strjoin(node->value, spl[1]);
                            
                        }
                        puts(final);
                        free(node->value);
                        node->value = ft_strdup(final);
                        if (search_node1(*saving_env, spl[0]))
                        {
                            puts("node2");
                            puts(node2->value);
                            char *add_equal;
                            char *res;
                            char *final;
                            char **old_value;
                            old_value = ft_split(node2->value, '=');
                            add_equal = ft_strjoin(spl[0], "=");
                            if (old_value[1])
                            {
                                res = ft_strjoin(add_equal, old_value[1]);
                                final = ft_strjoin(res, spl[1]);
                            }
                            else
                                final = ft_strjoin(node2->value, spl[1]);
                            free(node2->value);
                            node2->value = ft_strdup(final);
                        }
                        ft_free(old_value);
                        ft_free(spl);
                        ft_free(spl_p);
                    // }
                    
                }
            }
            i++;
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
                        final = ft_strjoin((*saving_expo)->value, "\"");
                        free(final);
                    }
					ft_free(sp);
                }
                else
                    final = (*saving_expo)->value;
                ft_putstr_fd("declare -x  ", 1);
                ft_putendl_fd(final, 1);
                // free(final);
                (*saving_expo) = (*saving_expo)->next;
                free(final);
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