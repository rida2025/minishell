/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:09:26 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 01:49:24 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skipandexpand(char *str, int *i, t_env *env)
{
	int		len;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	len = 1;
	while (str[*i + len] && !ft_strchr(STOPNOW, str[*i + len]))
		len++;
	tmp = ft_substr(str, (*i + 1), len - 1);
	tmp2 = ret_val(env, tmp);
	printf("skipandexpand>>>>%p\n", tmp2);
	if (!tmp2)
		tmp2 = ft_strdup("");
	*i += len;
	free(tmp);
	return (tmp2);
}
