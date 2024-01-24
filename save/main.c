/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/24 19:25:29 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokenze(t_tokenlist *info)
{
	t_tokenlist	*tmp;

	tmp = info;
	while (tmp)
	{
		printf("position:[%d], word:[%s], type:[%d], status:[%d]\n", tmp->info->position, \
		tmp->word, tmp->info->type, tmp->info->status);
		tmp = tmp->next;
	}
	printf("token where displayed\n");
}

void	print_parsing(t_parselist *info)
{
	t_parselist	*tmp;

	tmp = info;
	while (tmp)
	{
		printf("position:[%d], command:[%s], type:[%d], status:[%d]\n", tmp->info->position, \
		tmp->command, tmp->info->type, tmp->info->status);
		tmp = tmp->next;
	}
	printf("parsing where displayed\n");
}

int	main(int ac, char **argv, char **envp)
{
	char		*input;
	t_tokenlist	*info;
	t_parselist	*cmd;

	(void)ac;
	(void)argv;
	(void)envp;
	input = NULL;
	info = NULL;
	cmd = NULL;
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			break ;
		add_history(input);
		//create_info(&info, argc, argv, envp);
		insert_data(&info, input);
		//group_data(&info, input);
		//execute_input(info);
		print_tokenze(info);
		parser(info, &cmd);
		repair(&cmd);
		print_parsing(cmd);
		free_list(&info);
		free_listx(&cmd);
		free(input);
	}
	printf("outside\n");
	return (0);
}
