/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 21:07:34 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int signum) {
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
t_token	*parse_helper1(t_token *tmp, t_parselist **parse, char *str)
{
	int	old;

	old = 0;
	while (tmp && (tmp->key == 0 || tmp->status != 0 || tmp->key == 8
			|| tmp->key == 10))
	{
		old = tmp->key;
		if (!str)
			str = ft_strjoinx(ft_strdup(""), tmp->value);
		else
			str = ft_strjoinx(str, tmp->value);
		if (tmp)
			tmp = tmp->next;
	}
	insert_node(parse, str, old, 1);
	return (tmp);
}

void	parse_tokens(t_token **token, t_parselist **parse)
{
	t_token	*tmp;
	char	*str;

	str = NULL;
	tmp = *token;
	while (tmp)
	{
		if (tmp->key == 0 || tmp->status != 0 || tmp->key == 8
			|| tmp->key == 10)
			tmp = parse_helper1(tmp, parse, str);
		else
		{
			str = NULL;
			insert_node(parse, ft_strdup(tmp->value), tmp->key, 1);
			if (tmp)
				tmp = tmp->next;
		}
	}
}

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
	expand_variables(token, var->env, NULL);
	// print_tokenze(token);
	parse_tokens(token, parse);
	
	// print_parsing(parse);
	name_redirections(parse, &redirection);
	get_commands(parse, &commands);
	// print_parsing(parse);
	// print_redirections(redirection);
	// print_commands(commands);
	create_execution(&redirection, &commands, &var->cmd);
	// print_execution(&var->cmd);
	// printf("insertion of execution was done\n");
	// //check if the cmd is not null and pass it to execution and start executing
	//execution(var->cmd);
	redirect(var->cmd, var->env);
	free_listx(parse);
	free_redirections(&redirection);
	free_commands(&commands);
	free_execution(&var->cmd);
}

void	handup_call(void)
{
	write(1, "exit\n", 5);
	exit(exit_status_fun(0));
}

int	minishell(t_token **token, t_var *var, t_parselist	**parse)
{
	// (void)parse;
	while (1)
	{
		rl_catch_signals = 0;
		var->input = readline("minishell-1.0$ ");
		//printf("test: %s\n", var->input);
		if (!var->input)
			handup_call();
		if (check_s_dqoute(var->input))
		{
			free(var->input);
			ft_putstr_fd("minishell: quotes not closed\n", 2);
			continue ;
		}
		tokenize(token, var->input);
		// print_tokenze(token);
		if (check_tokenizing(token, var))
		{
			free(var->input);
			free_list(token);
			continue ;
		}
		do_rest(token, var, parse);
		add_history(var->input);
		free_list(token);
		free(var->input);
		 //system("leaks minishell");
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
	return (exit_status_fun(0));
}
