/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:23:08 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 17:08:12 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	forking(t_ex *it, int *fd, char **env, t_env *env_list)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		child_dup(fd, it);
		child_execution(it, env, env_list);
	}
	if (it->next == NULL)
		ft_last_cmd(pid);
	if (it->fd[0] != 0)
		close(it->fd[0]);
	if (it->fd[1] != 1)
		close(it->fd[1]);
}

void	init_exec(int *fd, int *tmp, int *i)
{
	fd[0] = -1;
	fd[1] = -1;
	*i = 0;
	*tmp = -1;
}

void	exist_status_handling(void)
{
	int	status;
	int	last_process_id;
	int	pid;

	pid = 1;
	last_process_id = ft_last_cmd(-1);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_process_id)
			exit_status(status);
	}
	if (g_id == 2)
	{
		write(2, "\n", 1);
		exit_status(130);
	}
}

void	execution(t_ex *it, char **env, t_env *env_list)
{
	int	tmp;
	int	fd[2];
	int	i;

	init_exec(fd, &tmp, &i);
	g_id = 5;
	while (it)
	{
		if (it->cmd[0] == NULL)
		{
			it = it->next;
			continue ;
		}
		piping(it, fd, i, &tmp);
		if (!it->next && i == 0 && is_builtin(it))
		{
			dup_built(fd, it, env_list, &i);
			it = it->next;
			continue ;
		}
		forking(it, fd, env, env_list);
		i++;
		it = it->next;
	}
	exist_status_handling();
}

void	redirect(t_ex *t, t_env *env_list)
{
	char	**env;

	env = list_to_tab(env_list);
	if (open_herdocs(env_list, t) == -1)
		return ;
	execution(t, env, env_list);
}
