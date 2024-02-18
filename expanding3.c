/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:09:26 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 21:32:16 by mel-jira         ###   ########.fr       */
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
	if (!tmp2)
		tmp2 = ft_strdup("");
	*i += len;
	free(tmp);
	return (tmp2);
}

char	*normal_expanding(t_env *env, char *str, int i)
{
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = NULL;
	if (ft_strlen(str) == 1)
		return (ft_strdup(str));
	if (str[i] && ft_isdigit(str[i]))
	{
		new_str = ft_substr(str, (i + 1), ft_strlen(str) - 2);
		return (new_str);
	}
	else if (str[i] && ft_strchr(EXP, str[i]))
	{
		if (ft_strlen(str) == 2 && str[i] == '?')
			new_str = ft_itoa(exit_status_fun(-500));
		else
			new_str = ret_val(env, &str[1]);
	}
	else
		new_str = bringme_new_str(str, &i);
	if (!new_str)
		return (ft_strdup(""));
	return (new_str);
}
