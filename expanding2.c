/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:09:30 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/20 09:04:08 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_advance_expander(char *str, t_env *env)
{
	int		i;
	char	*tmp;
	char	*new_str;
	char	*tmp_str;

	new_str = NULL;
	tmp = NULL;
	tmp_str = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			tmp = bringme_new_str(str, &i);
		else
			tmp = bring_me_expand(str, &i, env);
		tmp_str = new_str;
		if (!new_str)
			new_str = ft_strjoin(tmp, "");
		else
			new_str = ft_strjoin(new_str, tmp);
		free(tmp_str);
		free(tmp);
	}
	return (new_str);
}

char	*bringme_new_str(char *str, int *i)
{
	char	*new_str;
	int		len;

	new_str = NULL;
	len = 0;
	while (str[*i + len] && str[*i + len] != '$')
		len++;
	new_str = ft_substr(str, *i, len);
	*i += len;
	return (new_str);
}

char	*bring_me_expand(char *str, int *i, t_env *env)
{
	char	*new_str;

	new_str = NULL;
	if (str[*i + 1] && (ft_strchr(EXP, str[*i + 1]) || ft_isdigit(str[*i + 1])))
	{
		if (str[*i + 1] == '?')
		{
			new_str = handle_this();
			*i += 2;
		}
		else
			new_str = skipandexpand(str, i, env);
	}
	else
		new_str = get_variable(str, i);
	return (new_str);
}

char	*get_variable(char *str, int *i)
{
	char	*new_str;
	int		len;

	new_str = NULL;
	len = 1;
	if (ft_strlen(str) == 1)
		return (*i += 1, ft_strdup(str));
	while (str[*i + len] && !ft_strchr(STOPNOW, str[*i + len]))
		len++;
	new_str = ft_substr(str, *i, len);
	*i += len;
	return (new_str);
}

void	reset_expand(t_token *token)
{
	t_token	*remember;

	remember = token;
	if (token->next)
	{
		token = token->next;
		if (token->next && token->key == 9)
			token = token->next;
		while (token && token->key != 1 && token->key != 4
			&& token->key != 5 && token->key != 6 && token->key != 7
			&& token->key != 9)
		{
			if (token && token->status != 0)
				remember->expand = 0;
			if (token->next)
				token = token->next;
			else
				break ;
		}
	}
}
