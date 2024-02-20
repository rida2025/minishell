/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:40:37 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 12:38:10 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_add_to_list(char **equal_sign, char *cmd, t_env **tmp, char c)
{
	char	*help;

	help = ft_substr(cmd, 0, get_index(cmd, c));
	*equal_sign = ft_strchr(cmd, c);
	while (*tmp)
	{
		if (ft_strcmp(help, (*tmp)->key) == 0)
			break ;
		(*tmp) = (*tmp)->next;
	}
	free(help);
}

void	ft_contatenation(t_env **tmp, char *cmd, char *equa, t_env **exp_list)
{
	t_env	*new;

	if ((*tmp) == NULL)
	{
		new = (t_env *)ft_malloc(sizeof(t_env));
		new->key = ft_substr(cmd, 0, get_index(cmd, '+'));
		new->value = ft_strdup(equa + 2);
		add_back(exp_list, new);
	}
	else
	{
		if (!(*tmp)->value)
			(*tmp)->value = ft_strdup(equa + 2);
		else
			(*tmp)->value = ft_strjoin((*tmp)->value, equa + 2);
	}
}

void	sign_is_equa(char *cmd, t_env **exp_list, char *equal_sign)
{
	t_env	*new;

	new = (t_env *)ft_malloc(sizeof(t_env));
	if (!ft_strchr(cmd, '='))
	{
		new->key = ft_strdup(cmd);
		new->value = NULL;
		new->n_av = 1;
		add_back(exp_list, new);
	}
	else
	{
		new->key = ft_substr(cmd, 0, get_index(cmd, '='));
		new->value = ft_strdup(equal_sign + 1);
		new->n_av = 0;
		add_back(exp_list, new);
	}
}

t_env	*add_to_list(char *cmd, int flag, t_env *exp_list)
{
	int		i;
	char	*equal_sign;
	t_env	*tmp;

	tmp = (exp_list);
	i = 2;
	if (flag == 2)
	{
		help_add_to_list(&equal_sign, cmd, &tmp, '+');
		ft_contatenation(&tmp, cmd, equal_sign, &exp_list);
		return ((exp_list));
	}
	help_add_to_list(&equal_sign, cmd, &tmp, '=');
	if (tmp != NULL)
	{
		if (equal_sign)
		{
			tmp->value = ft_strdup(equal_sign + 1);
			tmp->n_av = 0;
		}
		return (exp_list);
	}
	sign_is_equa(cmd, &exp_list, equal_sign);
	return (exp_list);
}

void	init_find_path(int *i, int *c, int *fd)
{
	*i = 0;
	*c = 0;
	*fd = -1;
}
