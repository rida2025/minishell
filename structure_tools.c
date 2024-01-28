/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:29:35 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/18 18:11:36 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*add_information(t_info *infox)
{
	t_info	*node;

	node = malloc(sizeof(t_info));
	if (!node)
		return (NULL);
	node->position = infox->position;
	node->status = infox->status;
	node->type = infox->type;
	return (node);
}

void	add_node(t_tokenlist **infox, char *nword, int nposition)
{
	t_tokenlist	*new_node;
	t_tokenlist	*tmp;
	t_info		basic;

	tmp = *infox;
	basic.position = nposition;
	basic.type = 0;
	basic.status = 1;
	new_node = malloc(sizeof(t_tokenlist));
	new_node->info = add_information(&basic);
	new_node->word = nword;
	new_node->next = NULL;
	new_node->previous = NULL;
	if (!*infox)
		*infox = new_node;
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
		free(tmp->info);
		free(tmp);
	}
	//free(tmp);
}

void	free_listx(t_parselist **info)
{
	t_parselist	*tmp;

	while (*info)
	{
		tmp = *info;
		*info = (*info)->next;
		free(tmp->command);
		free(tmp->info);
		free(tmp);
	}
	//free(tmp);
}
