/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:15:49 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/25 10:56:13 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exp	*create_exp_node(char *key, char *value)
{
	t_exp	*node;

	node = (t_exp *)malloc(sizeof(t_exp));
	if (node == NULL)
		exit(1);
	node->key = key;

	node->value = value;
	node->next = NULL;
	return (node);
}

void	insert_exp_node(t_exp **head, char *key, char *value)
{
	t_exp	*new_node;

	if (value == NULL)
	{
		printf("HHHHHHH\n");
		exit(0);
	}
	new_node = create_exp_node(key, value);
	new_node->next = *head;
	*head = new_node;
}

t_exp	*get_exp(char **envp)
{
	t_exp	*exp_list;
	char	*equal_sign;
	int		i;

	exp_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign != NULL)
		{
			insert_exp_node(&exp_list, ft_substr(envp[i], 0,
					get_index(envp[i], '=')), equal_sign + 1);
			*equal_sign = '=';
		}
		else
			insert_exp_node(&exp_list, ft_substr(envp[i], 0, ft_strlen(envp[i])), NULL);
		i++;
		//execve()
	}
	//free_exp_list(exp_list);
	return (exp_list);
}
