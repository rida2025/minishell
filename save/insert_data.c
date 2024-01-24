/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:46:17 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/24 19:36:31 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(char *str)
{
	if (!ft_strncmp(str, "|", 1))
		return (1);
	if (!ft_strncmp(str, "\"", 1))
		return (2);
	if (!ft_strncmp(str, "\'", 1))
		return (3);
	if (!ft_strncmp(str, ">>", 2))
		return (7);
	if (!ft_strncmp(str, ">", 1))
		return (4);
	if (!ft_strncmp(str, "<<", 2))
		return (6);
	if (!ft_strncmp(str, "<", 1))
		return (5);
	if (!ft_strncmp(str, "$", 1))
		return (8);
	if (check_space(*str))
		return (9);
	return (0);
}

t_tokenlist	*tokenizing_status_helper(t_tokenlist *tmp, char *status, int value)
{
	tmp = tmp->next;
	while (tmp)
	{
		tmp->info->status = value;
		tmp = tmp->next;
		if (tmp && ft_strcmp(tmp->word, status))
		{
			tmp->info->status = 1;
			break ;
		}
	}
	if (tmp)
		tmp = tmp->next;
	return (tmp);
}

void	update_status(t_tokenlist **info)
{
	t_tokenlist	*tmp;

	tmp = *info;
	while (tmp)
	{
		if (!ft_strcmp(tmp->word, "\""))
		{
			tmp = tokenizing_status_helper(tmp, "\"", 2);
		}
		else if (!ft_strcmp(tmp->word, "\'"))
		{
			tmp = tokenizing_status_helper(tmp, "\'", 3);
		}
		else
			tmp->info->status = 1;
		if (tmp)
			tmp = tmp->next;
	}
}

void	update_nodes(t_tokenlist **info)
{
	t_tokenlist	*tmp;

	tmp = *info;
	while (tmp)
	{
		tmp->info->type = get_type(tmp->word);
		tmp = tmp->next;
	}
	printf("type was set\n");
	update_status(info);
	printf("status was set\n");
}

void	insert_data(t_tokenlist **info, char *input)
{
	char	*word;
	int		position;

	position = 0;
	while (input || *input)
	{
		word = get_word(&input);
		printf("word:[%s]\n", word);
		printf("input:[%s]\n", input);
		if (input)
			input = ft_strdup(input + ft_strlen(word));
		add_node(info, word, position);
		if (!*input)
			break ;
		position++;
	}
	update_nodes(info);
}
