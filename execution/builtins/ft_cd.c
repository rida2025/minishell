/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:29:14 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/16 00:49:57 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *search_key(t_env *env_list, char *var)
{
	while(env_list)
	{
		if(!ft_strcmp(env_list->key,var))
			return env_list->value;
		env_list = env_list->next;
	}
	return NULL;
}
t_env *get_node(t_env *env_list, char *var)
{
	while(env_list)
	{
		if(!ft_strcmp(env_list->key,var))
			return env_list;
		env_list = env_list->next;
	}
	return NULL;
}

void	ft_cd(char **cmd, t_env *env_list)
{
	t_env *tmp;
	char buffer[4000];
	if(cmd[1] == NULL)
	{
		if(chdir(search_key(env_list,"HOME")) != -1)
		{
			tmp = get_node(env_list,"PWD");
			if(tmp)
			{
				getcwd(buffer,3999);
				free(tmp->value);
				tmp->value = ft_strdup(buffer); 
			}
		}else
			write(2,"minishell: cd: HOME not set\n", 29);
	}
	
	getcwd(buffer,3999);
	if(chdir(cmd[1]) != -1)
	{
		tmp = get_node(env_list,"OLDPWD");
		if(tmp)
		{
			//free(tmp->value);
			tmp->value = ft_strdup(buffer);
		}
		else
			insert_env_node(&env_list,ft_strdup("OLDPWD"), ft_strdup(buffer));
		tmp = get_node(env_list,"PWD");
		if(tmp)
		{
			getcwd(buffer,3999);
			tmp->value = ft_strdup(buffer);
		}
	}
	// else
	// {
	// 	print_error("minishell", "cd", cmd[1], "No such file or directory");
	// }
}

// int main(int ac, char **av, char **envp)
// {
// 	char buffer[4000];
// 	t_env *env = get_env(envp);
	
// 	ft_cd(av, env);
// 	printf("%s\n", getcwd(buffer,3999));
// }