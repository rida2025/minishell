/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:48:43 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/08 16:07:34 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_token(t_token **info, int token, char *word)
{
	t_token	*tmp;
	t_token	*new_node;

	tmp = *info;
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->key = token;
	new_node->value = word;
	new_node->expand = 1;
	new_node->next = NULL;
	new_node->previous = NULL;
	if (token == 2 || token == 3)
		new_node->status = token - 1;
	else
		new_node->status = 0;
	if (!*info)
		*info = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		new_node->previous = tmp;
		tmp->next = new_node;
	}
}

int	quotes_size(char *str, int *i, char c, int *expand)
{
	int	j;

	j = 1;
	while (str[(*i) + j] && str[(*i) + j] != c)
	{
		if (str[(*i) + j] == '$')
			*expand = 1;
		j++;
	}
	return (++j);
}

int	get_size(char *input, int *i, int *expand)
{
	int	len;

	len = 0;
	if (input[(*i) + len] == '$')
		*expand = 1;
	while (input[(*i) + len] && !check_space(input[(*i) + len])
		&& input[(*i) + len] != '>' && input[(*i) + len] != '<'
		&& input[(*i) + len] != '|' && input[(*i) + len] != '\''
		&& input[(*i) + len] != '\"')
		len++;
	return (len);
}

int	get_size2(char *input, int *i)
{
	int	len;

	len = 0;
	while (input[(*i) + len] && !check_space(input[(*i) + len])
		&& input[(*i) + len] != '>' && input[(*i) + len] != '<'
		&& input[(*i) + len] != '|' && input[(*i) + len] != '\''
		&& input[(*i) + len] != '\"')
		len++;
	return (len);
}

