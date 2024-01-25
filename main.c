/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/20 00:24:42 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_structure(t_tokenlist *info)
{
	t_tokenlist	*tmp;

	tmp = info;
	while (tmp)
	{
		printf("word:[%s], type:[%d], status:[%d]\n", tmp->word, tmp->type, tmp->status);
		tmp = tmp->next;
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*input;
// 	t_tokenlist	*info;
// 	t_env		*vars;

// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	input = NULL;
// 	info = NULL;
// 	vars = get_env(envp);
// 	while (1)
// 	{
// 		input = readline("minishell: ");
// 		if (!input)
// 			break ;
// 		add_history(input);
// 		//create_info(&info, argc, argv, envp);
// 		insert_data(&info, input);
// 		//group_data(&info, input);
// 		//execute_input(info);
// 		print_structure(info);
// 		free_list(&info);
// 		free(input);
// 	}
// 	printf("outside\n");
// 	return (0);
// }
