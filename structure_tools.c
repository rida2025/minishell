/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:29:35 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/11 20:56:11 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	add_files_node(t_main_exec **execute, char *name, int key, int expando)
// {
// 	t_red		*new_node;
// 	t_main_exec	*tmp;

// 	tmp = *execute;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	while (tmp->node->next)
// 		tmp->node = tmp->node->next;
// 	while (tmp->node->red->next)
// 		tmp->node->red = tmp->node->red->next;
// 	new_node = malloc(sizeof(t_main_exec));
// 	new_node->name = ft_strdup(name);
// 	new_node->type = key;
// 	new_node->expand = expando;
// 	new_node->next = NULL;
// 	if (!tmp->node->red)
// 		tmp->node->red = new_node;
// }

// void	add_child_node(t_main_exec **execute, char *command, int key, int exp)
// {
// 	t_executelist	*new_node;
// 	t_main_exec		*tmp;

// 	tmp = *execute;
// 	new_node = malloc(sizeof(t_executelist));
// 	new_node->allcmd = ft_split(command, ' ');
// 	if (key == 4 || key == 5 || key == 6 || key == 7)
// 		add_files_node(execute, command, key, exp);
// 	else
// 	{
// 		new_node->red = NULL;
// 		new_node->fd[0] = -1;
// 		new_node->fd[1] = -1;
// 		new_node->next = NULL;
// 		if (!(*execute)->node)
// 			(*execute)->node = new_node;
// 		else
// 		{
// 			while (tmp->next)
// 				tmp = tmp->next;
// 			while (tmp->node->next)
// 				tmp->node = tmp->node->next;
// 			tmp->node = new_node;
// 		}
// 	}
// }

// void	add_node(t_main_exec **execution)
// {
// 	t_main_exec	*tmp;
// 	t_main_exec	*new_node;

// 	tmp = *execution;
// 	new_node = malloc(sizeof(t_main_exec));
// 	new_node->node = NULL;
// 	new_node->next = NULL;
// 	if (!*execution)
// 		*execution = new_node;
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_node;
// 	}
// }

void	put_node(t_redirections **redirection, char *str, int type)
{
	t_redirections	*tmp;
	t_redirections	*new_node;

	tmp = *redirection;
	new_node = malloc(sizeof(t_redirections));
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

void	put_nodex(t_commands **redirection, char *str, int type)
{
	t_commands	*tmp;
	t_commands	*new_node;

	tmp = *redirection;
	new_node = malloc(sizeof(t_commands));
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
