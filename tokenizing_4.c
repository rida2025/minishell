/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:11:59 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/18 20:57:45 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	string_size(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		i++;
	return (i);
}

void	extra_tokenizing(t_token *token, t_token **token2)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	strs = ft_split(token->value, "\t\n\v\f\r ");
	j = string_size(strs);
	while (strs[i])
	{
		insert_token2(token2, token->key, token->expand, strs[i]);
		if (j > 1)
			insert_token2(token2, 9, 1, ft_strdup(" "));
		j--;
		i++;
	}
}

void	just_insert_the_node(t_token *token, t_token **token2)
{
	insert_token2(token2, token->key, token->expand, ft_strdup(token->value));
}

void	tokenizing2(t_token **token, t_token **token2)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->key == 8)
		{
			extra_tokenizing(tmp, token2);
		}
		else
		{
			just_insert_the_node(tmp, token2);
		}
		tmp = tmp->next;
	}
}
