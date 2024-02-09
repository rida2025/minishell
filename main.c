/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/09 20:25:11 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokenze(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		printf("value:[%s], key:[%d], status:[%d], expand:[%d]\n",
			tmp->value, tmp->key, tmp->status, tmp->expand);
		tmp = tmp->next;
	}
	printf("tokens where displayed just a moment ago!\n");
}

void	print_parsing(t_parselist **token)
{
	t_parselist	*tmp;

	tmp = *token;
	while (tmp)
	{
		printf("value:[%s], key:[%d]\n",
			tmp->command, tmp->key);
		tmp = tmp->next;
	}
	printf("parsing was displayed just a moment ago!\n");
}

void	remove_quotes(t_token **token)
{
	t_token	*tmp;
	char	*tmp_value;

	tmp_value = NULL;
	tmp = *token;
	while (tmp)
	{
		if (tmp->status != 0)
		{
			tmp_value = tmp->value;
			tmp->value = ft_substr(tmp_value, 1, ft_strlen(tmp_value) - 2);
			free(tmp_value);
		}
		tmp = tmp->next;
	}
}

char	*bringme_new_str(char *str, int *i)
{
	char	*new_str;
	int		len;

	new_str = NULL;
	len = 0;
	while (str[*i + len] && str[*i + len] != '$')
		len++;
	new_str = ft_substr(str, *i, len);
	*i += len;
	return (new_str);
}

char	*skipandexpand(char *str, int *i, t_env *env)
{
	int		len;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	len = 1;
	while (str[*i + len] && !ft_strchr(STOPNOW, str[*i + len]))
		len++;
	tmp = ft_substr(str, (*i + 1), len - 1);
	tmp2 = ret_val(env, tmp);
	if (!tmp2)
		tmp2 = ft_strdup("");
	*i += len;
	free(tmp);
	return (tmp2);
}

char	*get_variable(char *str, int *i)
{
	char	*new_str;
	int		len;

	new_str = NULL;
	len = 1;
	if (ft_strlen(str) == 1)
		return (*i += 1, ft_strdup(str));
	while (str[*i + len] && !ft_strchr(STOPNOW, str[*i + len]))
		len++;
	new_str = ft_substr(str, *i, len);
	*i += len;
	return (new_str);
}

char	*bring_me_expand(char *str, int *i, t_env *env)
{
	char	*new_str;

	new_str = NULL;
	if (str[*i + 1] && (ft_strchr(EXP, str[*i + 1]) || ft_isdigit(str[*i + 1])))
	{
		if (str[*i + 1] == '?' && ft_strlen(&str[*i]) == 2)
			new_str = ft_itoa(exit_status_fun(0));
		else
			new_str = skipandexpand(str, i, env);
	}
	else
		new_str = get_variable(str, i);
	return (new_str);
}

char	*new_advance_expander(char *str, t_env *env)
{
	int		i;
	char	*tmp;
	char	*new_str;
	char	*tmp_str;

	new_str = NULL;
	tmp = NULL;
	tmp_str = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			tmp = bringme_new_str(str, &i);
		else
			tmp = bring_me_expand(str, &i, env);
		tmp_str = new_str;
		if (!new_str)
			new_str = ft_strjoin(tmp, "");
		else
			new_str = ft_strjoin(new_str, tmp);
		free(tmp_str);
		free(tmp);
	}
	return (new_str);
}

char	*normal_expanding(t_env *env, char *str, int i)
{
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = NULL;
	if (ft_strlen(str) == 1)
		return (ft_strdup(str));
	if (str[i] && ft_isdigit(str[i]))
	{
		new_str = ft_substr(str, (i + 1), ft_strlen(str) - 2);
		return (new_str);
	}
	else if (str[i] && ft_strchr(EXP, str[i]))
	{
		if (ft_strlen(str) == 2 && str[i] == '?')
			new_str = ft_itoa(exit_status_fun(0));
		else
			new_str = ret_val(env, &str[1]);
	}
	else
		new_str = bringme_new_str(str, &i);
	if (!new_str)
		return (ft_strdup(""));
	return (new_str);
}

int	there_is_heredoc(t_token *token)
{
	if (token->previous)
	{
		token = token->previous;
		if (token->key == 9)
			token = token->previous;
		if (token->key == 7)
			return (1);	
	}
	return (0);
}

void	expand_variables(t_token **token, t_env *env, char *str)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->value[0]
			&& ((tmp->key == 8 && tmp->status != 2)
				|| (tmp->key == 2 && tmp->status != 2)))
		{
			if (tmp->key == 8 && tmp->status != 2)
			{
				if (there_is_heredoc(tmp))
				{
					tmp = tmp->next;
					continue ;
				}
				str = normal_expanding(env, tmp->value, 1);
			}
			else if (tmp->key == 2 && tmp->status != 2)
				str = new_advance_expander(tmp->value, env);
			free(tmp->value);
			tmp->value = str;
		}
		tmp = tmp->next;
	}
}

void	do_magic(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->key == 8 && tmp->status == 0 && ft_strlen(tmp->value) == 1)
		{
			if (tmp->next && tmp->next->status != 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup("");
			}
		}
		tmp = tmp->next;
	}
}

t_token	*parse_helper1(t_token *tmp, t_parselist **parse, char *str)
{
	while (tmp && (tmp->key == 0 || tmp->status != 0 || tmp->key == 8
			|| tmp->key == 9 || tmp->key == 10))
	{
		if (!str)
			str = ft_strjoin("", tmp->value);
		else if (tmp->key == 9)
			str = ft_strjoin(str, " ");
		else
			str = ft_strjoin(str, tmp->value);
		if (tmp)
			tmp = tmp->next;
	}
	insert_node(parse, str, 0);
	return (tmp);
}

void	parse_spaces(t_parselist **parse)
{
	t_parselist	*tmp;
	char		*tmp2;

	tmp = *parse;
	tmp2 = NULL;
	while (tmp)
	{
		tmp2 = ft_skip_spaces(tmp->command);
		free(tmp->command);
		tmp->command = tmp2;
		tmp = tmp->next;
	}
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
			|| tmp->key == 9)
		{
			tmp = parse_helper1(tmp, parse, str);
		}
		else
		{
			str = NULL;
			insert_node(parse, ft_strdup(tmp->value), tmp->key);
			if (tmp)
				tmp = tmp->next;
		}
	}
	parse_spaces(parse);
}

void	reset_expand(t_token *token)
{
	t_token	*remember;

	remember = token;
	if (token->next)
	{
		if (token->next && token->next->status != 0)
			remember->expand = 0;
		if (token->next->next && token->next->next->status != 0)
			remember->expand = 0;
	}
}

void	set_expanding(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->key == 7)
			reset_expand(tmp);
		tmp = tmp->next;
	}
}

void	do_rest(t_token **token, t_parselist **parse, t_var *var)
{
	//in do magic i handle variable expanding where cases like $"" or $'' or $"x" or $'x'
	do_magic(token);
	remove_quotes(token);
	//set expand to 0 if there was a quotes after heredoc
	set_expanding(token);
	expand_variables(token, var->env, NULL);
	print_tokenze(token);
	parse_tokens(token, parse);
	print_parsing(parse);
	//it need to take parse and cmd
	// create_execution(parse, var->cmd);
	// //check if the cmd is not null and pass it to execution and start executing
	// execution(var->cmd);
	// free_execution(var->cmd);
}

int	check_pipes_front(t_token *token)
{
	t_token	*save;

	save = token;
	token = token->next;
	while (token && token->key == 9)
		token = token->next;
	if (!token || token->status != 0 ||
		(token->key != 8 && token->key != 0 && token->key != 10))
	{
		if (!token)
			return (pipe_error3(), 1);
		else
			return (pipe_error2(save->value), 1);
	}
	return (0);
}

int	check_pipes_back(t_token *token)
{
	t_token	*save;

	save = token;
	token = token->previous;
	if (token && token->key == 9)
		token = token->previous;
	if (!token || token->status != 0
		|| (token->key != 0 && token->key != 8 && token->key != 10))
	{
		return (pipe_error2(save->value), 1);
	}
	return (0);
}

int	check_pipes(t_token *token)
{
	if (ft_strlen(token->value) > 1)
		return (pipe_error1(), 1);
	if (check_pipes_back(token))
		return (1);
	if (check_pipes_front(token))
		return (1);
	return (0);
}

int	help_check_redirection(t_var *var, t_token *token, t_token **tmp)
{
	if (token->status != 0)
	{
		if (ft_strlen(token->value) == 2)
			return (redirection_error2(), 1);
	}
	if (token->key == 8 && (*tmp)->key != 7)
	{
		if (check_expand(token->value, var->env))
			return (redirection_error3(token->value), 1);
	}
	if (token->key == 8 && (*tmp)->key == 7)
	{
		if (check_heredoc_expand(token->value, var->env))
			return (redirection_error3(token->value), 1);
	}
	return (0);
}

int	check_redirection_front(t_token *token, t_var *var)
{
	t_token	*tmp;

	tmp = token;
	token = token->next;
	while (token && token->key == 9)
		token = token->next;
	if (token && (token->key == 0 || token->key == 2 || token->key == 3
			|| token->key == 8 || token->key == 10))
	{
		if (help_check_redirection(var, token, &tmp))
			return (1);
	}
	else
		return (redirection_error(), 1);
	return (0);
}

int	check_redirection(t_token *token, t_var *var)
{
	if (check_redirection_front(token, var))
		return (1);
	return (0);
}

int	help_checking(t_token *token, t_var *var)
{
	t_token	*tmp;

	tmp = token->next;
	if (token->key == 7)
	{
		while (tmp && tmp->key == 9)
			tmp = tmp->next;
		if (tmp && (tmp->key == 4 || tmp->key == 5 || tmp->key == 6
				|| tmp->key == 6 || tmp->key == 7 || tmp->key == 1))
			return (redirection_error4(), 1);
	}
	if (check_redirection(token, var))
		return (1);
	return (0);
}

int	check_tokenizing(t_token **token, t_var *var)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp && tmp->key == 1)
		{
			if (check_pipes(tmp))
				return (1);
		}
		else if (tmp && (tmp->key == 4 || tmp->key == 5 || tmp->key == 6
				|| tmp->key == 7))
		{
			if (help_checking(tmp, var))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	minishell(t_token **token, t_parselist **parse, t_var *var)
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
		do_rest(token, parse, var);
		free_list(token);
		free_listx(parse);
		free(var->input);
		// system("leaks minishell");
	}
	return (0);
}

void	init_the_minishell(t_token **token, t_parselist **cmd, t_all *all, t_var *var)
{
	(void)token;
	(void)cmd;
	(void)all;
	(void)var;
	//init everything u need later
}

void	free_everything(t_token **token, t_parselist **cmd)
{
	(void)token;
	(void)cmd;
	//free everything
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*token;
	t_parselist	*parse;
	t_all		all;
	t_var		var;

	(void)envp;
	(void)argv;
	(void)argc;
	init_the_minishell(&token, &parse, &all, &var);
	// handle env and export
	//check if minishell was
	//fix it later
	var.env = get_env(envp);
	//read the line and token it and parse it and check for syntax error
	minishell(&token, &parse, &var);
	//this will free the env and export
	free_everything(&token, &parse);
	return (exit_status_fun(0));
}
