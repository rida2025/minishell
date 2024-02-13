/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:59:06 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/13 14:00:06 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(t_token **token)
{
	t_token	*tmp;
	char	*tmp_value;

	tmp_value = NULL;
	tmp = *token;
	while (tmp)
	{
		if (tmp->status != 0)
		{
			tmp_value = tmp->value;
			tmp->value = ft_substr(tmp_value, 1, ft_strlen(tmp_value) - 2);
			free(tmp_value);
		}
		tmp = tmp->next;
	}
}

void	parse_spaces(t_parselist **parse)
{
	t_parselist	*tmp;
	char		*tmp2;

	tmp = *parse;
	tmp2 = NULL;
	while (tmp)
	{
		tmp2 = ft_skip_spaces(tmp->command);
		free(tmp->command);
		tmp->command = tmp2;
		tmp = tmp->next;
	}
}
