/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/28 11:06:59 by mel-jira         ###   ########.fr       */
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
	t_env		*env;

	(void)ac;
	(void)argv;
	env = get_env(envp);
	input = NULL;
	info = NULL;
	cmd = NULL;
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			break ;
		add_history(input);
		if (check_error(input) == 1)
			return (1);
		insert_data(&info, input);
		print_tokenze(info);
		parser(info, &cmd);
		repair(&cmd, env);
		print_parsing(cmd);
		free_list(&info);
		free_listx(&cmd);
		free(input);
	}
	return (0);
}
