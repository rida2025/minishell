/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:47:22 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/15 12:59:36 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_variable(t_token **token, char *input, t_info *var, int len)
{
	if (input[var->i] && input[var->i] == '$')
	{
		while (input[var->i + len] && !check_space(input[var->i + len])
			&& input[var->i + len] != '|' && input[var->i + len] != '>'
			&& input[var->i + len] != '<' && input[var->i + len] != '\''
			&& input[var->i + len] != '\"' && input[var->i + len] != '$'
			&& !ft_strchr(NONE_VALID, input[var->i + len]))
			len++;
		if (len > 0)
			insert_token(token, 8, ft_substr(input, var->i, len));
		var->i = var->i + len;
	}
}

void	insert_whitespaces(char *input, t_token **token, t_info *var, int len)
{
	while (input[var->i + len] && check_space(input[var->i + len]))
		len++;
	if (len > 0)
		insert_token(token, 9, ft_substr(input, var->i, len));
	var->i = var->i + len;
}
