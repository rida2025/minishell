/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/14 12:36:59 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_holyshit	*info;

	input = NULL;
	info = NULL;
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			break ;
		add_history(input);
		create_info(&info, argc, argv, envp);
		insert_data(&info, input);
		execute_input(info);
		free_input(&info);
		free(input);
	}
	return (0);
}
