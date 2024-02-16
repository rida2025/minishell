/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:14:23 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/16 14:28:14 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *get_env_help(void)
{
    t_env *env_list = malloc(sizeof(t_env)); // Allocate memory for the head node
    if (!env_list) {
        // Handle memory allocation failure if needed
        return NULL;
    }

    char buff[4096];

    env_list->key = ft_strdup("OLDPWD");
    env_list->value = NULL;
    env_list->next = NULL;
    env_list->next = malloc(sizeof(t_env));
    if (!env_list->next)
    {
        free(env_list);
        return NULL;
    }
    env_list->next->key = ft_strdup("PWD");
    env_list->next->value = ft_strdup(getcwd(buff, sizeof(buff)));
    env_list->next->next = NULL;
    env_list->next->next = malloc(sizeof(t_env));
    if (!env_list->next->next)
    {
        free(env_list->next);
        free(env_list);
        return NULL;
    }
    env_list->next->next->key = ft_strdup("SHLVL");
    env_list->next->next->value = ft_strdup("1");
    env_list->next->next->next = NULL;

    return env_list;
}
