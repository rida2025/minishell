/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 02:31:21 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/18 15:12:53 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strrcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	return (0);
}
