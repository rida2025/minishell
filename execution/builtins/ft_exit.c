/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:08:43 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/18 21:23:58 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cmd_size(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		i++;
	return (i);
}

void	exit_error1(void)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd("to many arguments\n", 2);
	exit_status_fun(255);
}

void	exit_error2(char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("miishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_status_fun(255);
}

int	check_numeric(char *exit)
{
	int	i;

	i = 0;
	while (exit && exit[i])
	{
		while (exit[i] && check_space(exit[i]))
			i++;
		while (exit[i] && exit[i] >= '0' && exit[i] <= '9')
			i++;
		if (exit[i] == '\0' && i > 0 && ft_isdigit(exit[--i]))
			return (0);
		else
			return (1);
	}
	return (0);
}

void	ft_exit(char **cmd)
{
	if (ft_cmd_size(cmd) == 2)
	{
		exit(exit_status_fun((unsigned char)ft_atoi(cmd[1])));
	}
	if (check_numeric(cmd[1]))
	{
		exit_error2(cmd[1]);
		exit(exit_status_fun(255));
	}
	if (ft_cmd_size(cmd) > 2)
	{
		exit_error1();
	}
	else
	{
		exit(exit_status_fun(0));
	}
}
