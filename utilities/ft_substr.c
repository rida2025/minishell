/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:23:49 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/02 14:37:49 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	lens;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start >= lens)
		return (ft_strdup(""));
	if ((lens - start) < len)
		str = malloc(sizeof(char) * ((lens - start) + 1));
	else
		str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
