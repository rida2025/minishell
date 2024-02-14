/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 04:05:50 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/14 19:52:54 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if(tmp->value != NULL)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
	
}
