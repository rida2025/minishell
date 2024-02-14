/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:29:14 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/14 21:15:18 by sacharai         ###   ########.fr       */
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
			free(tmp->value);
			tmp->value = ft_strdup(buffer);
		}
		else
			insert_env_node(&env_list,ft_strdup("OLDPWD"), ft_strdup(buffer));
		tmp = get_node(env_list,"PWD");
		if(tmp)
		{
			getcwd(buffer,3999);
			free(tmp->value);
			tmp->value = ft_strdup(buffer);
		}
	}
}

int main(int ac, char **av, char **envp)
{
	t_env *env_list = get_env(envp);
	ft_cd(av, env_list);
	char buffer[4000];
	getcwd(buffer,3999);
	puts(buffer);
}