/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:53:48 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 21:34:16 by mel-jira         ###   ########.fr       */
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

	tmp = NULL;
	while (*file)
	{
		tmp = *file;
		*file = (*file)->next;
		free(tmp->name);
		free(tmp);
	}
}

void	free_redirections(t_redirect **file)
{
	t_redirect		*tmp;

	while (*file)
	{
		tmp = *file;
		*file = (*file)->next;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
	}
}
