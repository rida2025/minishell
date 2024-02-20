/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 04:05:41 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/19 23:35:40 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_chr_unset(char *cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (is_alnum(cmd[i]) == 0)
		{
			print_error("minishell", "unset", cmd, "not a valid identifier");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	pars_args_unset(char *cmd)
{
	if (is_alpha(cmd[0]) == 0)
	{
		print_error("minishell", "unset", cmd, "not a valid identifier");
		return (-1);
	}
	return (check_chr_unset(cmd));
}

t_env	*remove_node(t_env **env_list, char *cmd)
{
	t_env	*tmp;
	t_env	*befor_node;

	tmp = (*env_list);
	befor_node = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, cmd))
			break ;
		befor_node = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (*env_list);
	if (befor_node)
		befor_node->next = tmp->next;
	else
		(*env_list) = (*env_list)->next;
	free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
	return (*env_list);
}

void	ft_unset(t_env **env_list, char **cmd)
{
	int	i;
	int	flag;

	if (cmd[1])
	{
		i = 1;
		while (cmd[i])
		{
			flag = 0;
			flag = pars_args_unset(cmd[i]);
			if (flag != -1)
				(*env_list) = remove_node((env_list), cmd[i]);
			else
				exit_status_fun(1);
			i++;
		}
	}
}
