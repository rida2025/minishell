/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:22:55 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/07 20:53:21 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status_fun(int exit_status)
{
	static int	value;

	if (exit_status)
		value = exit_status;
	return (value);
}

int	pipe_error1()
{
	ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
	exit_status_fun(258);
	return (1);
}

int	pipe_error2()
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	exit_status_fun(258);
	return (1);
}

int	pipe_error3()
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	exit_status_fun(258);
	return (1);
}

int	redirection_error()
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("`newline'\n", 2);
	exit_status_fun(258);
	return (1);
}

