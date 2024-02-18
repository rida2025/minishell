/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:39:16 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 22:29:32 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_nodex(t_cmd **redirection, char *str, int type)
{
	t_cmd	*tmp;
	t_cmd	*new_node;

	tmp = *redirection;
	new_node = ft_malloc(sizeof(t_cmd));
	new_node->cmd = str;
	new_node->key = type;
	new_node->next = NULL;
	if (!*redirection)
		*redirection = new_node;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	insert_node(t_parselist **parse, char *value, int type, int expando)
{
	t_parselist	*tmp;
	t_parselist	*new_node;

	tmp = *parse;
	new_node = ft_malloc(sizeof(t_parselist));
	new_node->command = value;
	new_node->key = type;
	new_node->expand = expando;
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
