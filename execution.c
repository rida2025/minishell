/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:12:18 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/12 15:50:39 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_all_size(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd)
	{
		if (cmd->key == 1)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

int	get_size(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd && cmd->key == 1)
		cmd = cmd->next;
	while (cmd && cmd->key != 1)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	create_execution(t_redirect **red, t_cmd **cmd, t_main_exec **exec)
{
	t_redirect		*tmp1;
	t_cmd			*tmp2;
	t_red			*tmp3;
	char			**strs;
	int				size;

	strs = NULL;
	tmp1 = *red;
	tmp2 = *cmd;
	size = get_all_size(tmp2);
	while (tmp1 || tmp2)
	{
		strs = malloc(sizeof(char *) * (size + 1));
		tmp1 = create_redirection_list(tmp1, &tmp3);
		tmp2 = create_commands_strs(tmp2, &strs);
		add_node(exec, strs, tmp3);
	}
}
