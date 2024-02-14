/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:30:27 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/23 18:51:55 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (str == NULL)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (i == len)
		return (-1);
	return (i);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		exit(1);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	insert_env_node(t_env **head, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	new_node->next = *head;
	*head = new_node;
}

t_env	*get_env(char **envp)
{
	t_env	*env_list;
	char	*equal_sign;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign != NULL)
		{
			insert_env_node(&env_list, ft_substr(envp[i], 0,
					get_index(envp[i], '=')), equal_sign + 1);
			*equal_sign = '=';
		}
		i++;
	}
	return (env_list);
}
