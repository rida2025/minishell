/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:29:35 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 22:29:17 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_red_node(t_red **redirection, char *str, int key, int expando)
{
	t_red	*tmp;
	t_red	*new_node;

	tmp = *redirection;
	new_node = ft_malloc(sizeof(t_redirect));
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

t_redirect	*create_redirection_list(t_redirect *redirect, t_red **red)
{
	t_red	*new_node;

	new_node = NULL;
	if (redirect && redirect->key == 1)
		redirect = redirect->next;
	while (redirect && redirect->key != 1)
	{
		add_red_node(&new_node, ft_strdup(redirect->value),
			redirect->key, redirect->expand);
		redirect = redirect->next;
	}
	*red = new_node;
	return (redirect);
}

t_cmd	*create_commands_strs(t_cmd *cmds, char ***strs, int size)
{
	int		i;

	i = 0;
	if (cmds && cmds->key == 1)
		cmds = cmds->next;
	while (cmds && i < size)
	{
		if (!cmds->cmd)
		{
			(*strs)[i] = NULL;
		}
		else
		{
			(*strs)[i] = ft_strdup(cmds->cmd);
		}
		i++;
		cmds = cmds->next;
	}
	(*strs)[i] = NULL;
	return (cmds);
}

void	add_node(t_ex **execution, char **strs, t_red **redirection)
{
	t_ex	*tmp;
	t_ex	*new_node;

	tmp = *execution;
	new_node = ft_malloc(sizeof(t_ex));
	new_node->cmd = strs;
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
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	put_node(t_redirect **redirection, char *str, int type, int expando)
{
	t_redirect	*tmp;
	t_redirect	*new_node;

	tmp = *redirection;
	new_node = ft_malloc(sizeof(t_redirect));
	new_node->value = str;
	new_node->key = type;
	new_node->expand = expando;
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
