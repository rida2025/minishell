/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:22:22 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/25 12:09:57 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	add_to_list(char **args)
{
	int		i;
	char    *equal_sign;
	t_env   *new;
	t_env   *tmp;

	i = 2;
	new = (t_env *)malloc(sizeof(t_env));
	tmp = new;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		new->key = ft_substr(args[i], 0, get_index(args[i], '='));
		new->value = equal_sign + 1;
		new = new->next;
		i++;
	}
	return (*tmp);
}
