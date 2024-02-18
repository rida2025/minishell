/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:33:01 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 22:24:34 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s1, int size)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = (char *)ft_malloc((len + 1) * sizeof(char));
	while (s1[i] != '\0' && size > 0)
	{
		str[i] = s1[i];
		i++;
		size--;
	}
	str[i] = '\0';
	return (str);
}
