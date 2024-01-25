/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:59:17 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/24 00:52:13 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ret_val(t_env *env_list,char *var)
{
    while (env_list)
	{
        if (ft_strcmp(env_list->key, var) == 0)
            return (env_list->value);
        env_list = env_list->next;
    }
    return (NULL);
}
