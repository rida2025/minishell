/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:53:48 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/11 20:56:24 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strings(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	free_list(t_token **info)
{
	t_token	*tmp;

	while (*info)
	{
		tmp = *info;
		*info = (*info)->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_listx(t_parselist **info)
{
	t_parselist	*tmp;

	while (*info)
	{
		tmp = *info;
		*info = (*info)->next;
		free(tmp->command);
		free(tmp);
	}
}

void	free_files(t_red **file)
{
	t_red		*tmp;

	while (*file)
	{
		tmp = *file;
		*file = (*file)->next;
		free(tmp->name);
		free(tmp);
	}
}

// void	free_nodes(t_executelist **nodes)
// {
// 	t_executelist		*tmp;

// 	while (*nodes)
// 	{
// 		tmp = *nodes;
// 		if (tmp->red)
// 			free_files(&tmp->red);
// 		*nodes = (*nodes)->next;
// 		free_strings(tmp->allcmd);
// 		free(tmp);
// 	}
// }

// void	free_execution(t_main_exec **info)
// {
// 	t_main_exec		*tmp;

// 	while (*info)
// 	{
// 		tmp = *info;
// 		if (tmp->node)
// 			free_nodes(&tmp->node);
// 		*info = (*info)->next;
// 		free(tmp->node);
// 		free(tmp);
// 	}
// }
