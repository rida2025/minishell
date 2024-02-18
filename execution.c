/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:12:18 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 22:27:29 by sacharai         ###   ########.fr       */
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
	if (!cmd)
		return (0);
	if (cmd && cmd->key == 1)
		cmd = cmd->next;
	while (cmd && cmd->key != 1)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	create_execution(t_redirect **red, t_cmd **cmd, t_ex **exec)
{
	t_redirect		*tmp1;
	t_cmd			*tmp2;
	t_red			*tmp3;
	char			**strs;
	int				size;

	strs = NULL;
	tmp1 = *red;
	tmp2 = *cmd;
	tmp3 = NULL;
	size = 0;
	while (tmp1 || tmp2)
	{
		size = get_size(tmp2);
		strs = ft_malloc(sizeof(char *) * (size + 1));
		tmp2 = create_commands_strs(tmp2, &strs, size);
		tmp1 = create_redirection_list(tmp1, &tmp3);
		add_node(exec, strs, &tmp3);
		tmp3 = NULL;
		strs = NULL;
	}
}
