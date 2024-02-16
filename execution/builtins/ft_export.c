/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:07:31 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/15 23:49:58 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_env *exp_list, char **allcmd)
{
	int		i;
	int		flag;

	printf("qweqweq%s %sqweqweqwe\n",allcmd[0],allcmd[1]);
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
				printf("+++++%s\n", (exp_list)->key);
			}
			i++;
		}
	}
	else
	{
		printf("eqweqwe\n");
		while ((exp_list))
		{
			if ((exp_list)->value)
				printf("declare -x %s=\"%s\"\n",
					(exp_list)->key, (exp_list)->value);
			else
				printf("declare -x %s\n", (exp_list)->key);
			(exp_list) = (exp_list)->next;
		}
		
	}
}


// int main(int ac, char **av, char **envp)
// {
// 	t_env *env = get_env(envp);
// 	ft_export(env, av);
	
// 	// while (env)
// 	// {
// 	// 	if (env->value)
// 	// 		printf("declare -x %s=\"%s\"\n",
// 	// 			env->key, env->value);
// 	// 	else
// 	// 		printf("declare -x %s\n", env->key);
// 	// 	env = env->next;
// 	// }
	
	
// }