/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:29:35 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/08 11:25:23 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_token **info)
{
	t_token	*tmp;

	while (*info)
	{
		tmp = *info;
		*info = (*info)->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_listx(t_parselist **info)
{
	t_parselist	*tmp;

	while (*info)
	{
		tmp = *info;
		*info = (*info)->next;
		free(tmp->command);
		free(tmp);
	}
}

void	insert_node(t_parselist **parse, char *value, int type)
{
	t_parselist	*tmp;
	t_parselist	*new_node;

	tmp = *parse;
	new_node = malloc(sizeof(t_parselist));
	new_node->command = value;
	new_node->key = type;
	new_node->next = NULL;
	new_node->previous = NULL;
	if (!*parse)
		*parse = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		new_node->previous = tmp;
		tmp->next = new_node;
	}
}
