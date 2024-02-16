/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:40:37 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/16 14:20:54 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	add_back(t_env **lst, t_env *ls)
{
	t_env	*tmp;

	if (!lst || !*lst || !ls)
		return ;
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = ls;
	tmp->next->next = NULL;
}

t_env	*add_to_list(char *cmd , int flag, t_env *exp_list)
{
	int		i;
	char	*equal_sign;
	t_env	*new;
	t_env	*tmp;
	char	*help;

	tmp = (exp_list);
	i = 2;
	if (flag == 2)
	{
		help = ft_substr(cmd, 0, get_index(cmd, '+'));
		equal_sign = ft_strchr(cmd, '+');
		while (tmp)
		{
			if (ft_strcmp(help, tmp->key) == 0)
				break ;
			tmp = tmp->next;
		}
		free(help);
		if (tmp == NULL)
		{
			new = (t_env *)malloc(sizeof(t_env));
			new->key = ft_substr(cmd, 0, get_index(cmd, '+'));
			new->value = ft_strdup(equal_sign + 2);
			add_back(&exp_list,new);
		}
		else
		{
			if (!tmp->value)
				tmp->value = ft_strdup(equal_sign + 2);
			else
				tmp->value = ft_strjoin(tmp->value,equal_sign + 2);
		}
		return ((exp_list));
	}
	help = ft_substr(cmd, 0, get_index(cmd, '='));
	equal_sign = ft_strchr(cmd, '=');
	while (tmp)
	{
		if (ft_strcmp(help,tmp->key) == 0)
			break ;
		tmp = tmp->next;
	}
	free(help);
	if (tmp != NULL)
	{
		if (equal_sign)
		{
			tmp->value = ft_strdup(equal_sign + 1);
			tmp->n_av = 0;
		}
		return ((exp_list));
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (!ft_strchr(cmd, '='))
	{
		new->key = ft_strdup(cmd);
		new->value = NULL;
		new->n_av = 1;
		add_back(&exp_list, new);
	}
	else
	{
		new->key = ft_substr(cmd, 0, get_index(cmd, '='));
		new->value = ft_strdup(equal_sign + 1);
		new->n_av = 0;
		add_back(&exp_list, new);
	}
	return (exp_list);
}
