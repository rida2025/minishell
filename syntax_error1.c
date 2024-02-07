/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:25:04 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/07 22:20:44 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	exit_status_fun(258);
}

void	check_squote(char *str, int *i, int *singlequote)
{
	(*singlequote)++;
	(*i)++;
	while (str[(*i)] != '\'' && str[(*i)])
		(*i)++;
	if (str[(*i)] == '\'')
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
		(*i)++;
	if (str[(*i)] == '"')
	{
		(*doublequote)++;
		(*i)++;
	}
}

int	check_s_dqoute(char *str)
{
	int	i;
	int	singlequote;
	int	doublequote;

	i = 0;
	singlequote = 0;
	doublequote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
				check_squote(str, &i, &singlequote);
			if (str[i] == '\"')
				check_dquote(str, &i, &doublequote);
		}
		else
			i++;
	}
	if ((singlequote % 2) || (doublequote % 2))
		return (syntax_error(), 1);
	return (0);
}

int	redirection_error2()
{
	ft_putstr_fd("minishell: No such file or directory\n", 2);
	exit_status_fun(258);
	return (1);
}
