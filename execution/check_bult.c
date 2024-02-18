/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 23:02:17 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/18 19:44:28 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_ex *cmds)
{
	if (!ft_strcmp(cmds->cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmds->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmds->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmds->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmds->cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmds->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmds->cmd[0], "unset"))
		return (1);
	else
		return (0);
}

int	exec_builtin(char **cmds, t_env *env_list)
{
	if (!ft_strcmp(cmds[0], "echo"))
		return (ft_echo(cmds), 0);
	else if (!ft_strcmp(cmds[0], "env"))
		return (ft_env(env_list), 0);
	else if (!ft_strcmp(cmds[0], "export"))
		return (ft_export(env_list, cmds), 0);
	else if (!ft_strcmp(cmds[0], "pwd"))
		return (ft_pwd(), 0);
	else if (!ft_strcmp(cmds[0], "exit"))
		return (ft_exit(cmds), 0);
	else if (!ft_strcmp(cmds[0], "unset"))
		return (ft_unset(&env_list, cmds), 0);
	else if (!ft_strcmp(cmds[0], "cd"))
		return (ft_cd(cmds, env_list), 0);
	else
		return (1);
}
