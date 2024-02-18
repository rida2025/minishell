/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:31:39 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/18 16:34:41 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_herdocs(t_env *env_list, t_ex *t)
{
	t_ex	*iterate;
	t_red	*a;

	iterate = t;
	while (iterate)
	{
		a = iterate->red;
		while (a)
		{
			if (a->type == 7)
			{
				iterate->fd[0] = heredoc(env_list, a->name, a->expand);
				if (iterate->fd[0] == -10)
					return (-1);
			}
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

void	add_back(t_env **lst, t_env *ls)
{
	t_env	*tmp;

	if (!lst || !*lst || !ls)
		return ;
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = ls;
	tmp->next->next = NULL;
}
