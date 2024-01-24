/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_holyshit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:38:52 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/15 22:20:59 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we will come back to this later
void	create_info(t_tokenlist **info, int argc, char **argv, char **envp)
{
	*info = malloc(sizeof(t_tokenlist));
	if (!*info)
		exit(1);
	(*info)->position = -1;
	(*info)->word = NULL;
	(*info)->type = -1;
	(*info)->next = NULL;
	(*info)->previous = NULL;
}
