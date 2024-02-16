/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:22:55 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 21:47:26 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status_fun(int exit_status)
{
	static int	value;

	if (exit_status != -500)
	{
		value = exit_status;
	}
	return (value);
}

int	pipe_error1(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	exit_status_fun(258);
	return (1);
}

int	pipe_error2(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	exit_status_fun(258);
	return (1);
}

int	redirection_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("`newline'\n", 2);
	exit_status_fun(258);
	return (1);
}
