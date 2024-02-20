/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:35:59 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/20 10:39:42 by sacharai         ###   ########.fr       */
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

void	expand_variables(t_token **token, t_env *env, char *str)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->value[0]
			&& ((tmp->key == 8 && tmp->status != 2)
				|| (tmp->key == 2 && tmp->status != 2)))
		{
			if (there_is_heredoc(tmp))
			{
				tmp = tmp->next;
				continue ;
			}
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
		if (!token)
			return (0);
		if (token && token->key == 9)
			token = token->previous;
		if (token && token->previous \
			&& token->status != 0)
			token = token->previous;
		if (token && token->key == 7)
			return (1);
	}
	return (0);
}
