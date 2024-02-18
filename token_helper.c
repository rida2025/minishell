/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:48:43 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/18 11:52:16 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_token(t_token **info, int token, char *word)
{
	t_token	*tmp;
	t_token	*new_node;

	tmp = *info;
	new_node = ft_malloc(sizeof(t_token));
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
		while (tmp && tmp->next)
			tmp = tmp->next;
		new_node->previous = tmp;
		tmp->next = new_node;
	}
}

void	insert_token2(t_token **info, int token, int ex, char *word)
{
	t_token	*tmp;
	t_token	*new_node;

	tmp = *info;
	new_node = ft_malloc(sizeof(t_token));
	new_node->key = token;
	new_node->value = word;
	new_node->expand = ex;
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
		while (tmp && tmp->next)
			tmp = tmp->next;
		new_node->previous = tmp;
		tmp->next = new_node;
	}
}
