/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:46:27 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/20 10:04:10 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_quote(t_token **token, char *input, t_info *var, int len)
{
	if (input[var->i] && check_space(input[var->i]))
		insert_whitespaces(input, token, var, 0);
	else if (input[var->i] && input[var->i] == '\'')
	{
		len = 1;
		while (input[var->i + len] && input[var->i + len] != '\'')
			len++;
		if (len > 0)
			insert_token(token, 3, ft_substr(input, var->i, len + 1));
		var->i = var->i + len + 1;
	}
	else if (input[var->i] && input[var->i] == '\"')
	{
		len = 1;
		while (input[var->i + len] && input[var->i + len] != '\"')
			len++;
		if (len > 0)
			insert_token(token, 2, ft_substr(input, var->i, len + 1));
		var->i = var->i + len + 1;
	}
}

void	insert_righr(t_token **token, char *input, t_info *var, int len)
{
	if (input[var->i] && input[var->i] == '>' && input[var->i + 1] != '>')
	{
		insert_token(token, 4, ft_substr(input, var->i, 1));
		var->i = var->i + 1;
		while (input[var->i] && input[var->i + 1]
			&& check_space(input[var->i + len]))
			len++;
		if (len > 0)
			insert_token(token, 9, ft_substr(input, var->i, len));
		var->i = var->i + len;
		var->flag = 1;
	}
}

void	insert_leftr(t_token **token, char *input, t_info *var, int len)
{
	if (input[var->i] && input[var->i] == '<' && input[var->i + 1] != '<')
	{
		insert_token(token, 5, ft_substr(input, var->i, 1));
		var->i = var->i + 1;
		while (input[var->i] && input[var->i + 1]
			&& check_space(input[var->i + len]))
			len++;
		if (len > 0)
			insert_token(token, 9, ft_substr(input, var->i, len));
		var->i = var->i + len;
		var->flag = 1;
	}
}

void	insert_append(t_token **token, char *input, t_info *var, int len)
{
	if (input[var->i] && input[var->i] == '>' && input[var->i + 1] == '>')
	{
		insert_token(token, 6, ft_substr(input, var->i, 2));
		var->i = var->i + 2;
		while (input[var->i] && input[var->i + 1]
			&& check_space(input[var->i + len]))
			len++;
		if (len > 0)
			insert_token(token, 9, ft_substr(input, var->i, len));
		var->i = var->i + len;
		var->flag = 1;
	}
}

void	insert_heredoc(t_token **token, char *input, t_info *var, int len)
{
	if (input[var->i] && input[var->i] == '<' && input[var->i + 1] == '<')
	{
		insert_token(token, 7, ft_substr(input, var->i, 2));
		var->i = var->i + 2;
		while (input[var->i] && input[var->i + 1]
			&& check_space(input[var->i + len]))
			len++;
		if (len > 0)
			insert_token(token, 9, ft_substr(input, var->i, len));
		var->i = var->i + len;
		var->flag = 1;
	}
}
