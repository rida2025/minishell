/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:41:29 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 21:44:35 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	if (signum == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status_fun(1);
	}
	else if (signum == 3)
	{
		rl_replace_line("", 0);
		return ;
	}
}

void	hangup_call(void)
{
	write(1, "exit\n", 5);
	exit(exit_status_fun(0));
}
