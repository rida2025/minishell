/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:35:59 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 21:07:37 by mel-jira         ###   ########.fr       */
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
			if (tmp->key == 8 && tmp->status != 2)
			{
				if (there_is_heredoc(tmp))
				{
					tmp = tmp->next;
					continue ;
				}
				str = normal_expanding(env, tmp->value, 1);
			}
			else if (tmp->key == 2 && tmp->status != 2)
			{
				if (there_is_heredoc(tmp))
				{
					tmp = tmp->next;
					continue ;
				}
				str = new_advance_expander(tmp->value, env);
			}
			free(tmp->value);
			tmp->value = str;
		}
		tmp = tmp->next;
	}
}

int	there_is_heredoc(t_token *token)
{
	if (token->previous)
	{
		token = token->previous;
		if (token->key == 9)
			token = token->previous;
		if (token->key == 7)
			return (1);	
	}
	return (0);
}

char	*normal_expanding(t_env *env, char *str, int i)
{
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = NULL;
	if (ft_strlen(str) == 1)
		return (ft_strdup(str));
	if (str[i] && ft_isdigit(str[i]))
	{
		new_str = ft_substr(str, (i + 1), ft_strlen(str) - 2);
		return (new_str);
	}
	else if (str[i] && ft_strchr(EXP, str[i]))
	{
		if (ft_strlen(str) == 2 && str[i] == '?')
			new_str = ft_itoa(exit_status_fun(-500));
		else
			new_str = ret_val(env, &str[1]);
	}
	else
		new_str = bringme_new_str(str, &i);
	if (!new_str)
		return (ft_strdup(""));
	return (new_str);
}
