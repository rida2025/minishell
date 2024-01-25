/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:18:49 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/25 11:09:16 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_env *exp_list, char **args)
{
	int		i;
	t_env	*new;

	i = 2;
	if (args[2])
	{
		pars_args(args, "export");
		*new = add_to_list(args);

	}
	else if (!args[2])
	{
		while (exp_list)
		{
			if (exp_list->value)
				printf("declare -x %s=\"%s\"\n", exp_list->key, exp_list->value);
			// else
			// printf("declare -x %s\n", exp_list->key);
			exp_list = exp_list->next;
		}
	}
}

int main(int ac, char **av, char **envp)
{
	t_env	*vars;

	vars = get_env(envp);
	if (ac >= 2)
	{
		if (ft_strcmp(av[1], "export") == 0)
			ft_export(vars, av);
		else
			printf("WRONG\n");
	}
	return 0;
}
