/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:03:04 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/07 22:23:55 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_expand(char *str, t_env *env)
{
	char	*new_str;

	new_str = NULL;
	if (ft_strchr(EXPANDO, str[1]))
		return (1);
	else
	{
		new_str = ret_val(env, str);
		if (!new_str)
			return (1);
	}
	return (0);
}
