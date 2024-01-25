/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 23:08:47 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/22 12:57:03 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return;

	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

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

void	check_chr(char **args, int len, char *cmd)
{
	int	i;
	int	j;

	i = 2;
	j = 1;
	while (i < len)
	{
		j = 1;
		while (args[i][j] && args[i][j] != '=')
		{
			//printf("%c\n", args[i][j]);
			if (is_alnum(args[i][j]) == 0)
			{
				print_error("minishell", cmd, args[i], "not a valid identifier");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	pars_args(char **args, char *cmd)
{
	int	len;
	int	i;
	int	j;

	len = 0;
	i = 2;
	while (args[len])
		len++;
	while (i < len)
	{
		if (is_alpha(args[i][0]) == 0)
		{
			print_error("minishell", cmd, args[i], "not a valid identifier");
			exit(1);
		}
		i++;
	}
	check_chr(args, len, cmd);
	printf("len ===== % d\n", len);
}
