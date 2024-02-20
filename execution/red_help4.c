/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:31:39 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 12:34:45 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_her_help(int *fd, t_red *a, int fg, t_env *env_list)
{
	if ((*fd) > 0)
		close(*fd);
	(*fd) = heredoc(env_list, a->name, a->expand);
	if (fg == 1)
		close(*fd);
}

int	open_herdocs(t_env *env_list, t_ex *t)
{
	t_ex	*iterate;
	t_red	*a;
	int		fg;

	iterate = t;
	while (iterate)
	{
		fg = 0;
		a = iterate->red;
		while (a)
		{
			if (a->type == 7)
			{
				open_her_help(&iterate->fd[0], a, fg, env_list);
				if (iterate->fd[0] == -10)
					return (-1);
			}
			else
				if (!fg && !base_redirection(iterate, a))
					fg = 1;
			a = a->next;
		}
		iterate = iterate->next;
	}
	return (0);
}

void	open_faild(char *name, t_ex *iterate, int fd)
{
	write(2, "minishell: ", 12);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	perror("");
	iterate->fd[fd] = -2;
	exit_status_fun(1);
}

int	opening(t_ex *iterate, t_red *a, int flag, int index)
{
	if (iterate->fd[index] != -1)
		close(iterate->fd[index]);
	iterate->fd[index] = open(a->name, flag, 0777);
	if (iterate->fd[index] == -1)
		return (0);
	return (1);
}

int	base_redirection(t_ex *iterate, t_red *a)
{
	if (a->type == 5)
	{
		if (!opening(iterate, a, O_RDONLY, 0))
			return (open_faild(a->name, iterate, 0), 0);
	}
	else if (a->type == 6)
	{
		if (!opening(iterate, a, O_RDWR | O_CREAT | O_APPEND, 1))
			return (open_faild(a->name, iterate, 1), 0);
	}
	else if (a->type == 4)
	{
		if (!opening(iterate, a, O_RDWR | O_CREAT | O_TRUNC, 1))
			return (open_faild(a->name, iterate, 1), 0);
	}
	return (1);
}
