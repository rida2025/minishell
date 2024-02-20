/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:14:23 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 17:09:30 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env_help(void)
{
	char	buff[4096];
	t_env	*env_list;

	env_list = ft_malloc(sizeof(t_env));
	env_list->key = ft_strdup("");
	env_list->value = NULL;
	env_list->next = ft_malloc(sizeof(t_env));
	env_list->next->key = ft_strdup("OLDPWD");
	env_list->next->value = NULL;
	env_list->next->next = ft_malloc(sizeof(t_env));
	env_list->next->next->key = ft_strdup("PWD");
	env_list->next->next->value = ft_strdup(getcwd(buff, sizeof(buff)));
	env_list->next->next->next = ft_malloc(sizeof(t_env));
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(env_list->next->next));
	env_list->next->next->next->key = ft_strdup("SHLVL");
	env_list->next->next->next->value = ft_strdup("1");
	env_list->next->next->next->next = NULL;
	return (env_list);
}
