/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/20 16:41:05 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_rest(t_token **token, t_var *var, t_parselist **parse)
{
	t_token		*token2;
	t_redirect	*redirection;
	t_cmd		*commands;

	redirection = NULL;
	commands = NULL;
	token2 = NULL;
	remove_dollar(token);
	remove_quotes(token);
	set_expanding(token);
	expand_variables(token, var->env, NULL);
	tokenizing2(token, &token2);
	parse_tokens(&token2, parse);
	name_redirections(parse, &redirection);
	get_commands(parse, &commands);
	create_execution(&redirection, &commands, &var->cmd);
	if (var->cmd && (var->cmd->red || var->cmd->cmd[0]))
		redirect(var->cmd, var->env);
	free_listx(parse);
	free_list(&token2);
	free_redirections(&redirection);
	free_commands(&commands);
	free_execution(&var->cmd);
}

void	free_rest(t_token **token, t_var *var)
{
	free_list(token);
	free(var->input);
}

void	minishell_help(t_token **token, t_var **var, t_parselist **parse)
{
	do_rest(token, (*var), parse);
	free_rest(token, (*var));
	signal(SIGQUIT, sigint_handler);
	signal(SIGINT, sigint_handler);
}

int	minishell(t_token **token, t_var *var, t_parselist	**parse)
{
	int	f_dup;

	f_dup = dup(STDIN_FILENO);
	while (1)
	{
		restore_stdin(&f_dup);
		rl_catch_signals = 0;
		var->input = readline("minishell-1.0$ ");
		mini_help(&var->input);
		if (check_s_dqoute(var->input))
		{
			free(var->input);
			ft_putstr_fd("minishell: quotes not closed\n", 2);
			continue ;
		}
		tokenize(token, var->input);
		if (check_tokenizing(token, var))
		{
			free(var->input);
			free_list(token);
			continue ;
		}
		minishell_help(token, &var, parse);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*token;
	t_parselist	*parse;
	t_var		var;

	(void)argv;
	(void)argc;
	token = NULL;
	parse = NULL;
	signal(SIGQUIT, sigint_handler);
	signal(SIGINT, sigint_handler);
	init_the_var(&var);
	var.env = get_env(envp);
	if (var.env == NULL)
		var.env = get_env_help();
	minishell(&token, &var, &parse);
	return (exit_status_fun(-500));
}
