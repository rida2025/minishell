/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:57:19 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/13 16:23:33 by mel-jira         ###   ########.fr       */
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
		if (!token)
			return (pipe_error2(), 1);
		else
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
	if (!token || token->key == 1)
	{
		if (token->status != 0 && ft_strlen(token->value) > 2)
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
	if (token->status != 0)
	{
		if (ft_strlen(token->value) == 2)
			return (redirection_error2(), 1);
	}
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
	token = token->next;
	while (token && token->key == 9)
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

int	check_redirection(t_token *token, t_var *var)
{
	if (check_redirection_front(token, var))
		return (1);
	return (0);
}

int	help_checking(t_token *token, t_var *var)
{
	t_token	*tmp;

	tmp = token->next;
	if (token->key == 7)
	{
		while (tmp && tmp->key == 9)
			tmp = tmp->next;
		if (tmp && (tmp->key == 4 || tmp->key == 5 || tmp->key == 6
				|| tmp->key == 6 || tmp->key == 7 || tmp->key == 1))
			return (redirection_error4(), 1);
	}
	if (check_redirection(token, var))
		return (1);
	return (0);
}

int	check_tokenizing(t_token **token, t_var *var)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp && tmp->key == 1)
		{
			if (check_pipes(tmp))
				return (1);
		}
		else if (tmp && (tmp->key == 4 || tmp->key == 5 || tmp->key == 6
				|| tmp->key == 7))
		{
			if (help_checking(tmp, var))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
