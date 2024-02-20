/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:28:14 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/20 10:07:22 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handler(const char *str)
{
	long double	handler;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	handler = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (((handler * 10 + (str[i] - 48)) * sign) > LONG_MAX)
			return (-1);
		if (((handler * 10 + (str[i] - 48)) * sign) < LONG_MIN)
			return (-1);
		handler = handler * 10 + (str[i] - 48);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	int			number;

	i = 0;
	sign = 1;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * sign);
}
