/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:40:06 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/12 11:22:55 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_val(t_env *env_list, char *var)
{
	t_env	*tmp;

	tmp = env_list;
	if (!var)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

void	name_redirections(t_token **token, t_redirect **redirection)
{
	t_token	*tmp;
	int		valuex;

	tmp = *token;
	valuex = 0;
	while (tmp)
	{
		if (tmp->key == 4 || tmp->key == 5 || tmp->key == 6
			|| tmp->key == 7 || tmp->key == 1)
		{
			valuex = tmp->key;
			tmp = tmp->next;
			if (tmp && tmp->key == 9)
				tmp = tmp->next;
			if (tmp)
			{
				tmp->key = -1;
				put_node(redirection, ft_strdup(tmp->value), valuex);
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	get_commands(t_token **token, t_cmd **commands)
{
	t_token	*tmp;
	int		value;
	char	*str;

	tmp = *token;
	value = 0;
	str = NULL;
	while (tmp)
	{
		if (tmp->key == 0 || (tmp->status != 0 && tmp->key != -1)
			|| tmp->key == 8 || tmp->key == 1 || tmp->key == 10)
		{
			value = tmp->key;
			str = ft_strdup(tmp->value);
			put_nodex(commands, str, value);
		}
		if (tmp)
			tmp = tmp->next;
	}
}
