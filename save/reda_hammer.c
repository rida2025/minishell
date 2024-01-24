/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reda_hammer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:52:25 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/24 19:52:06 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repair_start(t_parselist **main)
{
	t_parselist	*tmp;

	tmp = *main;
	while (tmp && tmp->info->type == 9)
	{
		free(tmp->command);
		tmp->command = NULL;
		tmp = tmp->next;
	}
	*main = tmp;
}

void	repair_end(t_parselist **main)
{
	t_parselist	*tmp;

	tmp = *main;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->previous && tmp->info->type == 9)
	{
		free(tmp->command);
		tmp->command = NULL;
		tmp = tmp->previous;
	}
	tmp->next = NULL;
}

// void	repair_midle(t_parselist **main)
// {
// 	t_parselist	*tmp;

// 	tmp = *main;
// im thinking about it ok
// }

void	repair(t_parselist **main)
{
	repair_start(main);
	repair_end(main);
}
