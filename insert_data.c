/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:46:17 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/15 22:14:03 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(char *str)
{
	if (*str == '|')
		return (1);
	if (*str == '"')
		return (2);
	if (*str == '\'')
		return (3);
	if (*str == '>')
		return (4);
	if (*str == '<')
		return (5);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (6);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (7);
	if (*str == '$')
		return (8);
	if (check_space(*str) == 0)
		return (9);
	return (0);
}

void	help_update_status(t_tokenlist **info)
{
	t_tokenlist	*tmp;

	tmp = *info;
	while (tmp)
	{
		if (ft_strcmp(tmp->word, "'") == 0)
			tmp = tmp->next;
		while (tmp)
		{
			tmp->status = 3;
			tmp = tmp->next;
			if (tmp && ft_strcmp(tmp->word, "'") == 0)
			{
				tmp->status = 1;
				break ;
			}
		}
		if (tmp)
		tmp = tmp->next;
	}
}

void	update_status(t_tokenlist **info)
{
	t_tokenlist	*tmp;

	tmp = *info;
	while (tmp)
	{
		if (ft_strcmp(tmp->word, "\"") == 0)
			tmp = tmp->next;
		while (tmp)
		{
			tmp->status = 2;
			tmp = tmp->next;
			if (tmp && ft_strcmp(tmp->word, "\"") == 0)
			{
				tmp->status = 1;
				break ;
			}
		}
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
		tmp->type = get_type(tmp->word);
		tmp = tmp->next;
	}
	printf("1 is done\n");
	update_status(info);
	help_update_status(info);
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
		if (!*input)
			break ;
		add_node(info, word, position);
		position++;
	}
	update_nodes(info);
}
