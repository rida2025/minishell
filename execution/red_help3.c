/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:22:52 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/18 10:22:58 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirections(t_ex *t)
{
	t_ex	*iterate;
	t_red	*a;

	iterate = t;
	while (iterate)
	{
		a = iterate->red;
		while (a)
		{
			if (!base_redirection(iterate, a))
				return ;
			a = a->next;
		}
		iterate = iterate->next;
	}
}

void	pipe_firstcmd(int *fd, t_ex	*it)
{
	pipe(fd);
	if (it->fd[1] == -1)
		it->fd[1] = fd[1];
	else
		close(fd[1]);
}

void	exit_status(int status)
{
	if (WIFEXITED(status))
		exit_status_fun(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit_status_fun(WTERMSIG(status) + 128);
}

void	pipe_secondcmd(int *tmp, int *fd, t_ex *it)
{
	close(*tmp);
	if (it->fd[0] == -1)
	{
		it->fd[0] = fd[0];
		*tmp = fd[0];
	}
	else
	{
		close(fd[0]);
		*tmp = -1;
	}
	close (fd[1]);
	pipe(fd);
	if (it->fd[1] == -1)
		it->fd[1] = fd[1];
	else
		close(fd[1]);
}

void	pipe_lastcmd(int *tmp, int *fd, t_ex *it)
{
	close(*tmp);
	if (it->fd[0] == -1)
		it->fd[0] = fd[0];
	else
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
}
