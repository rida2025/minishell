/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/18 19:30:14 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_rest(t_token **token, t_var *var, t_parselist **parse)
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
	expand_variables(token, var->env, NULL, 0);
	parse_tokens(token, parse);
	name_redirections(parse, &redirection);
	get_commands(parse, &commands);
	create_execution(&redirection, &commands, &var->cmd);
	redirect(var->cmd, var->env);
	free_listx(parse);
	free_redirections(&redirection);
	free_commands(&commands);
	free_execution(&var->cmd);
}

void	free_rest(t_token **token, t_var *var)
{
	free_list(token);
	free(var->input);
}

int	minishell(t_token **token, t_var *var, t_parselist	**parse)
{
	// (void)parse;
	int	f_dup;
	f_dup = dup(STDIN_FILENO);
	while (1)
	{
		if(ttyname(0) == NULL)
			if(dup2(f_dup, STDIN_FILENO) == -1)
				close(f_dup);
		rl_catch_signals = 0;
		var->input = readline("minishell-1.0$ ");
		if (!var->input)
			hangup_call();
		if (ft_strcmp(var->input, ""))
			add_history(var->input);
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
		do_rest(token, var, parse);
		free_rest(token, var);
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
