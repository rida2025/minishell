/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printdata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:45:10 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/20 10:20:13 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokenze(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		printf("value:[%s], key:[%d], status:[%d], expand:[%d]\n",
			tmp->value, tmp->key, tmp->status, tmp->expand);
		tmp = tmp->next;
	}
	printf("tokens where displayed just a moment ago!\n\n");
}

void	print_parsing(t_parselist **token)
{
	t_parselist	*tmp;

	tmp = *token;
	while (tmp)
	{
		printf("value:[%s], key:[%d], expand[%d]\n",
			tmp->command, tmp->key, tmp->expand);
		tmp = tmp->next;
	}
	printf("parsing was displayed just a moment ago!\n\n");
}

void	print_redirections(t_redirect *redirection)
{
	t_redirect	*tmp;

	tmp = redirection;
	while (tmp)
	{
		printf("value:[%s], key:[%d], expand=[%d]\n",
			tmp->value, tmp->key, tmp->expand);
		tmp = tmp->next;
	}
	printf("redirections where displayed just a moment ago!\n\n");
}

void	print_commands(t_cmd *commands)
{
	t_cmd	*tmp;

	tmp = commands;
	while (tmp)
	{
		printf("value:[%s], key:[%d]]\n", tmp->cmd, tmp->key);
		tmp = tmp->next;
	}
	printf("commands where displayed just a moment ago!\n\n");
}

void	print_execution(t_ex *tmp)
{
	t_red		*redirection;
	int			i;

	redirection = NULL;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd && tmp->cmd[i])
		{
			printf("command:[%s]\n", tmp->cmd[i]);
			i++;
		}
		redirection = tmp->red;
		while (redirection && redirection->name)
		{
			printf("filename:[%s], type=[%d], expand=[%d]\n",
				redirection->name, redirection->type, redirection->expand);
			redirection = redirection->next;
		}
		tmp = tmp->next;
	}
	printf("execution where displayed just a moment ago!\n\n");
}
