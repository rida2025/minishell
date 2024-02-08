/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:32:10 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/08 19:41:52 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_error3(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	exit_status_fun(258);
	return (1);
}

int	redirection_error4(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	exit_status_fun(258);
	return (1);
}
