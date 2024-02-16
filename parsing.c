/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:40:06 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/16 01:48:35 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_val(t_env *env_list, char *var)
{
	t_env	*tmp;

	tmp = env_list;
	if (!var)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
		{
			printf("1ret_val>>>>%p\n", &(tmp->value));
			char * ss = ft_strdup(tmp->value);
			printf("2ret_val>>>>%p\n", &ss);
			return (ss);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	words_amout(t_parselist *parse)
{
	int	i;

	i = 0;
	while (parse)
	{
		if (parse->key == 1)
			return (i);
		if (parse->key == 0 || parse->key == 10 || parse->key == 8
			|| parse->key == 2 || parse->key == 3)
			i++;
		parse = parse->next;
	}
	return (i);
}

int	redirection_amount(t_parselist *parse)
{
	int	i;

	i = 0;
	while (parse)
	{
		if (parse->key == 1)
			return (i);
		if (parse->key == 4 || parse->key == 5 || parse->key == 6
			|| parse->key == 7)
			i++;
		parse = parse->next;
	}
	return (i);
}

void	name_redirections(t_parselist **parse, t_redirect **redirection)
{
	t_parselist	*tmp;
	t_parselist	*remember;
	int			flag;

	tmp = *parse;
	remember = NULL;
	flag = 0;
	while (tmp)
	{
		if (redirection_amount(tmp) == 0 && !flag)
		{
			put_node(redirection, NULL, -1, -1);
			while (tmp && tmp->key != 1)
				tmp = tmp->next;
		}
		if (tmp && (tmp->key == 4 || tmp->key == 5 || tmp->key == 6
				|| tmp->key == 7))
		{
			flag = 1;
			remember = tmp;
			tmp = tmp->next;
			if (tmp && tmp->key == 9)
				tmp = tmp->next;
			if (tmp)
			{
				tmp->key = -1;
				put_node(redirection, ft_strdup(tmp->command), remember->key, remember->expand);
			}
		}
		if (tmp && tmp->key == 1)
			put_node(redirection, ft_strdup(tmp->command), 1, 1);
		if (tmp)
			tmp = tmp->next;
	}
}

void	get_commands(t_parselist **parse, t_cmd **commands)
{
	t_parselist	*tmp;
	int			value;
	char		*str;
	int			flag;

	tmp = *parse;
	value = 0;
	str = NULL;
	flag = 0;
	while (tmp)
	{
		if (words_amout(tmp) == 0 && !flag)
		{
			put_nodex(commands, NULL, -1);
			while (tmp && tmp->key != 1)
				tmp = tmp->next;
		}
		if (!tmp)
			break ;
		if (tmp->key == 0
			|| ((tmp->key == 2 || tmp->key == 3) && tmp->key != -1)
			|| tmp->key == 8 || tmp->key == 1 || tmp->key == 10)
		{
			flag = 1;
			if (tmp->key == 1)
				flag = 0;
			value = tmp->key;
			str = ft_strdup(tmp->command);
			put_nodex(commands, str, value);
		}
		if (tmp)
			tmp = tmp->next;
	}
}
