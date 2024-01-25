/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:16:46 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/23 01:19:27 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_list(t_env *head)
{
	while (head != NULL)
	{
		printf("Key: %s, Value: %s\n", head->key, head->value);
		head = head->next;
	}
}

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	ft_env(t_env *env_list)
{
				
}