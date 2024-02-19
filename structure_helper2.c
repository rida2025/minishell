/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:11:03 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 20:11:34 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_execution(t_ex **cmd)
{
	t_ex		*tmp;
	t_red		*tmp2;

	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		free_strings(tmp->cmd);
		tmp2 = tmp->red;
		free_files(&tmp2);
		free(tmp);
	}
}

void	free_commands(t_cmd **cmds)
{
	t_cmd		*tmp;

	while (*cmds)
	{
		tmp = *cmds;
		*cmds = (*cmds)->next;
		free(tmp->cmd);
		free(tmp);
	}
}

void	free_env(t_env **envs)
{
	t_env		*tmp;

	while (*envs)
	{
		tmp = *envs;
		*envs = (*envs)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
