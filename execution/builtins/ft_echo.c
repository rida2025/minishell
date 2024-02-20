/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 04:48:23 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 01:26:56 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	len_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static	int	check_line(char *args)
{
	int	i;

	i = 0;
	if (args[i] != '-' || (args[i] == '-' && args[i + 1] != 'n'))
		return (1);
	else
	{
		i++;
		while (args[i] && args[i] == 'n')
			i++;
		if (args[i] == '\0')
			return (0);
		else
			return (1);
	}
}

void	ft_echo_help(char **args, int i, int *n_to_n, int *n_line)
{
	while (args[i])
	{
		if (!check_line(args[i]) && *n_to_n == 1)
		{
			*n_line = 1;
			i++;
		}
		else
		{
			*n_to_n = 0;
			ft_putstr_fd(args[i], 1);
			if (args[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	n_to_n;
	int	n_line;

	i = 1;
	n_to_n = 0;
	n_line = 0;
	if (len_args(args) > 1)
	{
		if (!check_line(args[i]))
		{
			n_line = 1;
			n_to_n = 1;
			i++;
		}
		ft_echo_help(args, i, &n_to_n, &n_line);
	}
	if (n_line == 0)
		write(1, "\n", 1);
	exit_status_fun(0);
	return (0);
}
