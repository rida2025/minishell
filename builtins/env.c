/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:16:46 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/17 21:10:27 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
void	print_env(char *str)
{
	str = getenv(str);
	printf("%s\n", str);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return (str + i);
	else
		return (NULL);
}

t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	node->key = ft_strdup(key);
	if (node->key == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	node->value = ft_strdup(value);
	if (node->value == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	node->next = NULL;
	return (node);
}

void	insert_env_node(t_env **head, const char *key, const char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	new_node->next = *head;
	*head = new_node;
}

void	print_env_list(t_env *head)
{
	while (head != NULL)
	{
		printf("Key: %s, Value: %s\n", head->key, head->value);
		head = head->next;
	}
}

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env_list;
	char	*equal_sign;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			insert_env_node(&env_list, envp[i], equal_sign + 1);
			*equal_sign = '=';
		}
		i++;
	}
	//print_env_list(env_list);
	print_env("PATH");
	free_env_list(env_list);
	return (0);
}
