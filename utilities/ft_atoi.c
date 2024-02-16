/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:28:14 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/15 11:30:38 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_handler(const char *str, int sign)
{
	long long	handler;
	int			i;

	i = 0;
	handler = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (((handler * 10 + (str[i] - 48)) * sign) > 2147483647)
			return (-1);
		if (((handler * 10 + (str[i] - 48)) * sign) < -2147483648)
			return (1);
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
	if (ft_handler(&str[i], sign) == 1)
		return (0);
	if (ft_handler(&str[i], sign) == -1)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * sign);
}
