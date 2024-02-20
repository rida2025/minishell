/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:08:43 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 10:10:20 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_error1(void)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd("to many arguments\n", 2);
	exit_status_fun(1);
}

void	exit_error2(char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("miishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(exit_status_fun(255));
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

void	exit_helper(char **cmd, int i, int args)
{
	int	error;

	error = 0;
	if (args == 2)
	{
		if (cmd[1][i] == '+' || cmd[1][i] == '-')
			i++;
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				error = 1;
				break ;
			}
			i++;
		}
		if (error == 0 && (ft_handler(cmd[1]) == -1 || cmd[1][0] == '\0'))
			error = 1;
		if (error == 0)
			exit(exit_status_fun((unsigned char)ft_atoi(cmd[1])));
		else
			exit_error2(cmd[1]);
	}
}

void	ft_exit(char **cmd)
{
	int	args;

	args = ft_cmd_size(cmd);
	exit_helper(cmd, 0, args);
	if (args > 1 && (check_numeric(cmd[1]) || cmd[1][0] == '\0'))
		exit_error2(cmd[1]);
	if (args > 2)
		exit_error1();
	else
		exit(exit_status_fun(0));
}
