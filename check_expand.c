/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:03:04 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/09 14:42:54 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_expand(char *str, t_env *env)
{
	char	*new_str;

	new_str = NULL;
	if (ft_strlen(str) == 1)
		return (0);
	if (ft_strchr(EXPANDO, str[1]))
		return (0);
	else
	{
		new_str = ret_val(env, &str[1]);
		if (!new_str)
			return (1);
	}
	return (0);
}

int	count_words(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && check_space(str[i]))
			i++;
		if (str[i] && !check_space(str[i]))
			words++;
		while (str[i] && !check_space(str[i]))
			i++;
	}
	return (words);
}

int check_heredoc_expand(char *str, t_env *env)
{
	char	*new_str;

	new_str = NULL;
	if (ft_strlen(str) == 1)
		return (0);
	if (ft_strchr(EXPANDO, str[1]))
		return (0);
	else
	{
		new_str = ret_val(env, &str[1]);
		if (!new_str)
			return (1);
		if (count_words(new_str) > 1 || count_words(new_str) == 0)
			return (1);
	}
	return (0);
}
