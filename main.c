/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/13 18:12:57 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_rest(t_token **token, t_var *var)
{
	t_redirect	*redirection;
	t_cmd		*commands;

	redirection = NULL;
	commands = NULL;
	//in do magic i handle variable expanding where cases like $"" or $'' or $"x" or $'x'
	remove_dollar(token);
	remove_quotes(token);
	//set expand to 0 if there was a quotes after heredoc
	set_expanding(token);
	expand_variables(token, var->env, NULL);
	name_redirections(token, &redirection);
	get_commands(token, &commands);
	print_tokenze(token);
	print_redirections(redirection);
	print_commands(commands);
	create_execution(&redirection, &commands, &var->cmd);
	print_execution(&var->cmd);
	// printf("insertion of execution was done\n");
	// //check if the cmd is not null and pass it to execution and start executing
	//execution(var->cmd);
	free_redirections(&redirection);
	free_commands(&commands);
	free_execution(&var->cmd);
}

int	minishell(t_token **token, t_var *var)
{
	while (1)
	{
		var->input = readline("minishell: ");
		if (!var->input)
			break ;
		add_history(var->input);
		if (check_s_dqoute(var->input))
		{
			free(var->input);
			ft_putstr_fd("minishell: quotes not closed\n", 2);
			continue ;
		}
		tokenize(token, var->input);
		print_tokenze(token);
		if (check_tokenizing(token, var))
		{
			free(var->input);
			free_list(token);
			continue ;
		}
		do_rest(token, var);
		free_list(token);
		//free_listx(parse);
		free(var->input);
		// system("leaks minishell");
	}
	return (0);
}

void	init_the_var(t_var *var)
{
	var->expand = 0;
	var->input = NULL;
	var->env = NULL;
	var->cmd = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*token;
	//t_parselist	*parse;
	//t_all		all;
	t_var		var;

	(void)envp;
	(void)argv;
	(void)argc;
	init_the_var(&var);
	// handle env and export
	//check if minishell was
	//fix it later
	var.env = get_env(envp);
	//read the line and token it and parse it and check for syntax error
	minishell(&token, &var);
	return (exit_status_fun(0));
}
