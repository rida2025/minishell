/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:35:59 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/18 12:28:59 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_expanding(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->key == 7)
			reset_expand(tmp);
		tmp = tmp->next;
	}
}

void	remove_dollar(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->key == 8 && tmp->status == 0 && ft_strlen(tmp->value) == 1)
		{
			if (tmp->next && tmp->next->status != 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup("");
			}
		}
		tmp = tmp->next;
	}
}

void	choose_type(t_token *tmp, int *index)
{
	if (tmp->key == 8 && tmp->status != 2)
		*index = 1;
	else if (tmp->key == 2 && tmp->status != 2)
		*index = 2;
}

void	expand_variables(t_token **token, t_env *env, char *str, int index)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->value[0]
			&& ((tmp->key == 8 && tmp->status != 2)
				|| (tmp->key == 2 && tmp->status != 2)))
		{
			choose_type(tmp, &index);
			if (there_is_heredoc(tmp))
			{
				tmp = tmp->next;
				continue ;
			}
			if (index == 1)
				str = normal_expanding(env, tmp->value, 1);
			else if (index == 2)
				str = new_advance_expander(tmp->value, env);
			tmp->value = str;
		}
		tmp = tmp->next;
	}
}

int	there_is_heredoc(t_token *token)
{
	while (token->previous)
	{
		token = token->previous;
		if (token)
			return (0);
		if (token && token->key == 9)
			token = token->previous;
		if (token && token->status != 0)
			token = token->previous;
		if (token && token->key == 7)
			return (1);
	}
	return (0);
}
