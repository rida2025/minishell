/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:40:42 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 22:23:02 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static	char	*ft_nbrcpy(char *dest, int nbr, int len)
{
	int	sign;

	sign = 0;
	if (nbr < 0)
	{
		sign++;
		nbr = nbr * -1;
	}
	if (len > 0)
		dest[len--] = '\0';
	while (len >= 0)
	{
		dest[len--] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	if (sign > 0)
		dest[0] = '-';
	return (dest);
}

static	char	*min_int(void)
{
	char	*ret;

	ret = ft_malloc(12);
	ft_strlcpy(ret, "-2147483648", 12);
	return (ret);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_nbrlen(n);
	if (n == -2147483648)
		return (min_int());
	str = (char *)ft_malloc((len + 1) * sizeof(char));
	str = ft_nbrcpy(str, n, len);
	return (str);
}
