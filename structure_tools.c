/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:29:35 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/15 22:15:04 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_tokenlist **info, char *nword, int nposition)
{
	t_tokenlist	*new_node;
	t_tokenlist	*tmp;

	tmp = *info;
	new_node = malloc(sizeof(t_tokenlist));
	new_node->position = nposition;
	new_node->word = nword;
	new_node->type = 0;
	new_node->status = 1;
	new_node->next = NULL;
	new_node->previous = NULL;
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

void	free_list(t_tokenlist **info)
{
	t_tokenlist	*tmp;

	while (*info)
	{
		tmp = *info;
		*info = (*info)->next;
		free(tmp->word);
		free(tmp);
	}
	//free(tmp);
}
