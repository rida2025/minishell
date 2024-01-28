/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reda_hammer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:52:25 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/28 12:56:34 by mel-jira         ###   ########.fr       */
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

void	repair_midle(t_parselist **main)
{
	t_parselist	*tmp;
	t_parselist	*tmp2;

	tmp = *main;
	tmp2 = tmp;
	while (tmp)
	{
		if (tmp->info->position > 1 && \
			(tmp->info->type == 4 || tmp->info->type == 5 \
			|| tmp->info->type == 6 || tmp->info->type == 7 \
			|| tmp->info->type == 0 || tmp->info->type == 1))
		{
			tmp2 = tmp->previous;
			while (tmp2 && tmp2->info->type == 9)
			{
				free(tmp2->command);
				tmp2->command = NULL;
				tmp2 = tmp2->previous;
			}
			tmp2->next = tmp;
			tmp->previous = tmp2;
		}
		tmp = tmp->next;
	}
}

void	expand_variabes(t_parselist **main, t_env *env)
{
	t_parselist *tmp;
	char		*str;

	str = NULL;
	tmp = *main;
	while (tmp)
	{
		if (tmp && tmp->info->type == 8 && tmp->info->status != 3)
		{
			printf("expand:[%s]\n", tmp->command);
			str = ret_val(env, tmp->command);
			if (!str)
				return ;
			tmp->command = ft_strdup(str);
		}
		tmp = tmp->next;
	}
}

void	repair_position(t_parselist **main)
{
	int			i;
	t_parselist	*tmp;

	tmp = *main;
	i = 0;
	while (tmp)
	{
		tmp->info->position = i;
		i++;
		tmp = tmp->next;
	}
}

void	repair(t_parselist **main, t_env *env)
{
	repair_start(main);
	//printf("here 1\n");
	//repair_midle(main);
	//printf("here 2\n");
	repair_end(main);
	//printf("here 3\n");
	expand_variabes(main, env);
	//printf("here 4\n");
	repair_position(main);
}
