/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:57:19 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 21:34:49 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes_front(t_token *token)
{
	t_token	*save;

	save = token;
	token = token->next;
	while (token && token->key == 9)
		token = token->next;
	if (!token || token->key == 1)
	{
		if (token && token->status != 0 && ft_strlen(token->value) > 2)
			return (0);
		if (!token)
			return (pipe_error2(), 1);
		return (pipe_error1(save->value), 1);
	}
	return (0);
}

int	check_pipes_back(t_token *token)
{
	t_token	*save;

	save = token;
	token = token->previous;
	if (token && token->key == 9)
		token = token->previous;
	if (!token || token->key == 1 || token->key == 4 || token->key == 5
		|| token->key == 6 || token->key == 7)
	{
		if (token && token->status != 0 && ft_strlen(token->value) > 2)
			return (0);
		return (pipe_error1(save->value), 1);
	}
	return (0);
}

int	check_pipes(t_token *token)
{
	if (ft_strlen(token->value) > 1)
		return (pipe_error1(token->value), 1);
	if (check_pipes_back(token))
		return (1);
	if (check_pipes_front(token))
		return (1);
	return (0);
}

int	help_check_redirection(t_var *var, t_token *token, t_token **tmp)
{
	if (token->key == 8 && (*tmp)->key != 7)
	{
		if (check_expand(token->value, var->env)
			|| check_ambiguous(token->value, var->env))
			return (redirection_error3(token->value), 1);
	}
	return (0);
}

int	check_redirection_front(t_token *token, t_var *var)
{
	t_token	*tmp;

	tmp = token;
	if (token->key == 7)
		return (0);
	token = token->next;
	if (token && token->key == 9)
		token = token->next;
	if (token && (token->key == 0 || token->key == 2 || token->key == 3
			|| token->key == 8 || token->key == 10))
	{
		if (help_check_redirection(var, token, &tmp))
			return (1);
	}
	else
		return (redirection_error(), 1);
	return (0);
}
