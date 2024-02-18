/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:46:28 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/17 06:02:17 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *name, char *cmd, char *str, char *message)
{
	if (name)
		ft_putstr_fd(name, 2);
	if (cmd)
	{
		if (name)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
	}
	if (str)
	{
		if (name || cmd)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	if (message)
	{
		if (name || cmd || str)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (-1);
}

int	is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	is_alnum(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_chr(char *cmd)
{
	int	i;

	i = 1;
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] == '+' && cmd[i + 1] == '=')
			return (2);
		if (is_alnum(cmd[i]) == 0)
		{
			print_error("minishell", "export", cmd, "not a valid identifier");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	pars_args(char *cmd)
{
	if (is_alpha(cmd[0]) == 0)
	{
		print_error("minishell", "export", cmd, "not a valid identifier");
		return (-1);
	}
	return (check_chr(cmd));
}
