/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:25:04 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/27 12:26:14 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if all right redirection are valid
// check if all left redirection are valid
// check if heredoc is valid
// check if append to right is valid
// check if pipe valid
// check if double quote is closed
// check if single quote is closed

void	syntax_error(void)
{
	write(2, "syntax error\n", 14);
}

void	check_squote(char *str, int *i, int *singlequote)
{
	(*singlequote)++;
	(*i)++;
	while (str[(*i)] != '\'' && str[(*i)])
	{
		(*i)++;
	}
	if (str[(*i)] == '"')
	{
		(*singlequote)++;
		(*i)++;
	}
}

void	check_dquote(char *str, int *i, int *doublequote)
{
	(*doublequote)++;
	(*i)++;
	while (str[(*i)] != '"' && str[(*i)])
	{
		(*i)++;
	}
	if (str[(*i)] == '"')
	{
		(*doublequote)++;
		(*i)++;
	}
}

int	check_error(char *str)
{
	int	i;
	int	singlequote;
	int	doublequote;

	i = 0;
	singlequote = 0;
	doublequote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			check_squote(str, &i, &singlequote);
		else if (str[i] == '"')
			check_dquote(str, &i, &doublequote);
		else
			i++;
	}
	if ((singlequote % 2) || (doublequote % 2))
	{
		return (syntax_error(), 1);
	}
	return (0);
}

