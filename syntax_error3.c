/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:32:10 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/20 03:45:36 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_error3(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	exit_status_fun(1);
	return (1);
}

int	redirection_error4(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	exit_status_fun(258);
	return (1);
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
		if (tmp && tmp->key == 9)
			tmp = tmp->next;
		if ((tmp && (tmp->key == 4 || tmp->key == 5 || tmp->key == 6
					|| tmp->key == 7 || tmp->key == 1)) || !tmp)
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
