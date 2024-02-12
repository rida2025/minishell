/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:29:35 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/12 15:50:01 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_red_node(t_red **redirection, char *str, int key, int expando)
{
	t_red	*tmp;
	t_red	*new_node;

	tmp = *redirection;
	new_node = malloc(sizeof(t_redirect));
	new_node->name = str;
	new_node->type = key;
	new_node->expand = expando;
	new_node->next = NULL;
	if (!*redirection)
		*redirection = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_red	*create_redirection_list(t_redirect *redirection, t_red	*red)
{
	while (redirection)
	{
		if (redirection->key == 1)
			break ;
		add_red_node();
		redirection = redirection->next;
	}
	return (red);
}

t_cmd	*create_commands_strs(t_cmd *cmds, char ***strs)
{
	int		i;
	int		size;

	i = 0;
	strs = NULL;
	size = get_size(cmds);
	while (i < size)
	{
		(*strs)[i] = ft_strdup(cmds->cmd);
		i++;
		cmds = cmds->next;
	}
	return (cmds);
}

void	add_node(t_main_exec **execution, char **strs, t_red **redirection)
{
	t_main_exec	*tmp;
	t_main_exec	*new_node;

	tmp = *execution;
	new_node = malloc(sizeof(t_main_exec));
	new_node->allcmd = strs;
	new_node->fd[0] = -1;
	new_node->fd[1] = -1;
	if (!*redirection)
		new_node->red = NULL;
	else
		new_node->red = *redirection;
	new_node->next = NULL;
	if (!*execution)
		*execution = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	put_node(t_redirect **redirection, char *str, int type)
{
	t_redirect	*tmp;
	t_redirect	*new_node;

	tmp = *redirection;
	new_node = malloc(sizeof(t_redirect));
	new_node->value = str;
	new_node->key = type;
	new_node->next = NULL;
	if (!*redirection)
		*redirection = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	put_nodex(t_cmd **redirection, char *str, int type)
{
	t_cmd	*tmp;
	t_cmd	*new_node;

	tmp = *redirection;
	new_node = malloc(sizeof(t_cmd));
	new_node->cmd = str;
	new_node->key = type;
	new_node->next = NULL;
	if (!*redirection)
		*redirection = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}
