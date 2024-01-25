/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:43:37 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/18 15:44:16 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (str == NULL)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (i == len)
		return (-1);
	return (i);
}
