/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:28:05 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/17 05:40:32 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_built(int *fd, t_ex *it, t_env *env_list, int *i)
{
	if (it->fd[0] != 0)
	{
		fd[0] = dup(0);
		dup2(it->fd[0], 0);
		close(it->fd[0]);
	}
	if (it->fd[1] != 1)
	{
		fd[1] = dup(1);
		dup2(it->fd[1], 1);
		close(it->fd[1]);
	}
	exec_builtin(it->cmd, env_list);
	if (fd[0] != -1)
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
	if (fd[1] != -1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	(*i)++;
}

void	child_dup(int *fd, t_ex *it)
{
	if (it->fd[0] == -2 || it->fd[1] == -2)
		exit(1);
	if (fd[1] != 1 && (it->fd[1] != fd[1]))
		close(fd[1]);
	if (fd[0] != 0 && (it->fd[0] != fd[0]))
		close(fd[0]);
	if ((it->fd[1] != -1) && (it->fd[1] != 1))
	{
		dup2(it->fd[1], 1);
		close(it->fd[1]);
	}
	if (it->fd[0] != -1 && it->fd[0] != 0)
	{
		dup2(it->fd[0], 0);
		close(it->fd[0]);
	}
}

void	child_execution(t_ex *it, char **env, t_env *env_list)
{
	char	*path;
	char	*full_path;

	if (is_builtin(it))
	{
		exec_builtin(it->cmd, env_list);
		exit(0);
	}
	else
	{
		full_path = check_env_path(env);
		path = find_path(full_path, it->cmd[0]);
		execve(path, it->cmd, env);
		exit_status_fun(127);
	}
}

void	piping(t_ex *it, int *fd, int i, int *tmp)
{
	if (it->next)
	{
		if (i == 0)
			pipe_firstcmd(fd, it);
		else
			pipe_secondcmd(tmp, fd, it);
	}
	else
		pipe_lastcmd(tmp, fd, it);
}

int	ft_last_cmd(int i)
{
	static int	last;

	if (i == -1)
		return (last);
	last = i;
	return (last);
}
