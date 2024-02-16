/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:46:17 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 20:10:23 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function will return a new str without space at it start and its end
char	*ft_skip_spaces(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = NULL;
	i = 0;
	j = 0;
	while (str[j])
		j++;
	while (str[i] && check_space(str[i]))
		i++;
	while (j > i && check_space(str[j - 1]))
		j--;
	return (ft_substr(str, i, j - i));
}

//this function will insert a word
void	insert_word(t_token **info, char *input, t_info *var, int len)
{
	if (input[var->i] && input[var->i] != '-' && input[var->i] != '|'
		&& input[var->i] != '>' && input[var->i] != '<'
		&& input[var->i] != '\"' && input[var->i] != '\''
		&& input[var->i] != '$'
		&& var->flag && !check_space(input[var->i]))
	{
		while (input[var->i + len] && input[var->i + len] != '\''
			&& input[var->i + len] != '\"' && input[var->i + len] != '>'
			&& input[var->i + len] != '<' && input[var->i + len] != '$'
			&& input[var->i + len] != '|' && !check_space(input[var->i + len])
			&& input[var->i + len] != '-')
			len++;
		if (len > 0 && var->flag)
		{
			insert_token(info, 0, ft_substr(input, var->i, len));
			var->flag = 0;
		}
		var->i = var->i + len;
		len = 0;
		while (input[var->i + len] && check_space(input[var->i + len]))
			len++;
		if (len > 0)
			insert_token(info, 9, ft_substr(input, var->i, len));
		var->i = var->i + len;
	}
}

void	handle_options(t_token **info, char *input, t_info *var, int len)
{
	if ((input[var->i] && input[var->i] != '\''
			&& input[var->i] != '\"' && input[var->i] != '|'
			&& input[var->i] != '$' && input[var->i] != '<'
			&& input[var->i] != '>' && !check_space(input[var->i])
			&& !var->flag) || input[var->i] == '-')
	{
		while (input[var->i + len] && input[var->i + len] != '\"'
			&& input[var->i + len] != '\'' && input[var->i + len] != '$'
			&& input[var->i + len] != '>' && input[var->i + len] != '<'
			&& input[var->i + len] != '|' && input[var->i + len] != ' ')
			len++;
		if (len > 0)
			insert_token(info, 10, ft_substr(input, var->i, len));
		var->i = var->i + len;
	}
}

void	insert_pipe(t_token **info, char *input, t_info *var, int len)
{
	if (input[var->i] && input[var->i] == '|')
	{
		while (input[var->i + len] && input[var->i + len] == '|')
			len++;
		if (len > 0)
			insert_token(info, 1, ft_substr(input, var->i, len));
		var->i = var->i + len;
		len = 0;
		while (input[var->i + len] && check_space(input[var->i + len]))
			len++;
		if (len > 0)
			insert_token(info, 9, ft_substr(input, var->i, len));
		var->i = var->i + len;
		var->flag = 1;
	}
}

void	tokenize(t_token **token, char *input)
{
	t_info	var;

	var.i = 0;
	var.flag = 1;
	if (!input)
		return ;
	input = ft_skip_spaces(input);
	while (input && input[var.i])
	{
		insert_word(token, input, &var, 0);
		handle_options(token, input, &var, 0);
		insert_pipe(token, input, &var, 0);
		insert_quote(token, input, &var, 0);
		insert_righr(token, input, &var, 0);
		insert_leftr(token, input, &var, 0);
		insert_append(token, input, &var, 0);
		insert_heredoc(token, input, &var, 0);
		insert_variable(token, input, &var, 1);
	}
	free(input);
}
