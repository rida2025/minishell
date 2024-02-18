/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:42:32 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 21:43:11 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parse_helper1(t_token *tmp, t_parselist **parse, char *str)
{
	t_token	*remember;
	int		flag;

	remember = NULL;
	flag = 0;
	while (tmp && (tmp->key == 0 || tmp->status != 0 || tmp->key == 8
			|| tmp->key == 10))
	{
		if (!flag)
		{
			remember = tmp;
			flag = 1;
		}
		if (!str)
			str = ft_strjoinx(ft_strdup(""), tmp->value);
		else
			str = ft_strjoinx(str, tmp->value);
		if (tmp)
			tmp = tmp->next;
	}
	insert_node(parse, str, remember->key, remember->expand);
	return (tmp);
}

void	parse_tokens(t_token **token, t_parselist **parse)
{
	t_token	*tmp;
	char	*str;

	str = NULL;
	tmp = *token;
	while (tmp)
	{
		if (tmp->key == 0 || tmp->status != 0 || tmp->key == 8
			|| tmp->key == 10)
			tmp = parse_helper1(tmp, parse, str);
		else
		{
			str = NULL;
			insert_node(parse, ft_strdup(tmp->value), tmp->key, tmp->expand);
			if (tmp)
				tmp = tmp->next;
		}
	}
}
