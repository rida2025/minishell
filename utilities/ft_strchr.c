/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:45:24 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/02 14:37:34 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)&(s[i]));
		i++;
	}
	return (NULL);
}
