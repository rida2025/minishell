/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:07:31 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 17:08:51 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(t_env *exp_list)
{
	while ((exp_list))
	{
		if ((exp_list)->value)
			printf("declare -x %s=\"%s\"\n",
				(exp_list)->key, (exp_list)->value);
		else
		{
			if ((exp_list)->key[0])
				printf("declare -x %s\n", (exp_list)->key);
		}
		(exp_list) = (exp_list)->next;
	}
}

void	ft_export(t_env *exp_list, char **allcmd)
{
	int		i;
	int		flag;

	if (allcmd[1])
	{
		i = 1;
		while (allcmd[i])
		{
			flag = 0;
			flag = pars_args(allcmd[i]);
			if (flag != -1)
			{
				exp_list = add_to_list(allcmd[i], flag, exp_list);
			}
			else
				exit_status_fun(1);
			i++;
		}
	}
	else
		print_export(exp_list);
}
