/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 04:05:50 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/16 01:00:54 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// char    *ft_strnstr(const char *h, const char *n, size_t len)
// {
//         size_t  i;
//         size_t  j;
//         size_t  ln;
//         char    *str;

//         i = 0;
//         j = 0;
//         ln = ft_strlen(n);
//         str = (char *)h;
//         if (ln == 0)
//                 return (str);
//         while (str[i] && i < len)
//         {
//                 j = 0;
//                 while (str[i + j] == n[j] && i + j < len && n[j] && str[i + j])
//                         j++;
//                 if (j == ln)
//                         return (str + i);
//                 i++;
//         }
//         return (0);
// }

void	ft_env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value == NULL)
			printf("test: %s", tmp->value);
		if(tmp->value != NULL)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putchar_fd('=', 1);
			if (strstr(tmp->value, ""))
				ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
	
}
