/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:12:19 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 20:26:30 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_nameredirections(t_parselist *tmp,
t_redirect **redirection, int *flag)
{
	t_parselist	*remember;

	remember = NULL;
	if (tmp && (tmp->key == 4 || tmp->key == 5 || tmp->key == 6
			|| tmp->key == 7))
	{
		*flag = 1;
		remember = tmp;
		tmp = tmp->next;
		if (tmp && tmp->key == 9)
			tmp = tmp->next;
		if (tmp)
		{
			tmp->key = -1;
			put_node(redirection, ft_strdup(tmp->command),
				remember->key, remember->expand);
		}
	}
}

void	name_redirections(t_parselist **parse, t_redirect **redirection)
{
	t_parselist	*tmp;
	t_parselist	*remember;
	int			flag;

	tmp = *parse;
	remember = NULL;
	flag = 0;
	while (tmp)
	{
		if (redirection_amount(tmp) == 0 && !flag)
		{
			put_node(redirection, NULL, -1, -1);
			while (tmp && tmp->key != 1)
				tmp = tmp->next;
		}
		help_nameredirections(tmp, redirection, &flag);
		if (tmp && tmp->key == 1)
			put_node(redirection, ft_strdup(tmp->command), 1, 1);
		if (tmp)
			tmp = tmp->next;
	}
}

void	help_getcommand(t_parselist *tmp, t_cmd **commands, int *flag)
{
	char	*str;
	int		value;

	str = NULL;
	value = 0;
	if (tmp->key == 0
		|| ((tmp->key == 2 || tmp->key == 3) && tmp->key != -1)
		|| tmp->key == 8 || tmp->key == 1 || tmp->key == 10)
	{
		*flag = 1;
		if (tmp->key == 1)
			*flag = 0;
		value = tmp->key;
		str = ft_strdup(tmp->command);
		put_nodex(commands, str, value);
	}
}

void	get_commands(t_parselist **parse, t_cmd **commands)
{
	t_parselist	*tmp;
	int			value;
	int			flag;

	tmp = *parse;
	value = 0;
	flag = 0;
	while (tmp)
	{
		if (words_amout(tmp) == 0 && !flag)
		{
			put_nodex(commands, NULL, -1);
			while (tmp && tmp->key != 1)
				tmp = tmp->next;
		}
		if (!tmp)
			break ;
		help_getcommand(tmp, commands, &flag);
		if (tmp)
			tmp = tmp->next;
	}
}
