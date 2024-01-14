/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_holyshit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:38:52 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/14 12:50:41 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_info(t_holyshit **info, int argc, char **argv, char **envp)
{
	*info = malloc(sizeof(t_holyshit));
	if (!*info)
		exit(1);
	(*info)->position = 1;
	(*info)->cmd = NULL;
	(*info)->cmdpath = NULL;
	(*info)->type = -1;
	(*info)->next = NULL;
}
