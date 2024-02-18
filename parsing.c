/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:40:06 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 20:13:50 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_val(t_env *env_list, char *var)
{
	t_env	*tmp;
	char	*str;

	tmp = env_list;
	if (!var)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
		{
			str = ft_strdup(tmp->value);
			return (str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	words_amout(t_parselist *parse)
{
	int	i;

	i = 0;
	while (parse)
	{
		if (parse->key == 1)
			return (i);
		if (parse->key == 0 || parse->key == 10 || parse->key == 8
			|| parse->key == 2 || parse->key == 3)
			i++;
		parse = parse->next;
	}
	return (i);
}

int	redirection_amount(t_parselist *parse)
{
	int	i;

	i = 0;
	while (parse)
	{
		if (parse->key == 1)
			return (i);
		if (parse->key == 4 || parse->key == 5 || parse->key == 6
			|| parse->key == 7)
			i++;
		parse = parse->next;
	}
	return (i);
}
