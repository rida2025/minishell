/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 03:21:43 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/14 23:04:35 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_malloc(size_t len)
{
	void	*ptr;

	ptr = malloc(len);
	if (!ptr)
		exit(1);
	return (ptr);
}

char	**list_to_tab(t_env *env_list)
{
	int		count;
	t_env	*current;
	char	**tab;
	int		i;

	count = 0;
	i = 0;
	current = env_list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	tab = (char **)ft_malloc((count + 1) * sizeof(char *));
	current = env_list;
	while (current != NULL)
	{
		tab[i] = (char *)ft_malloc((ft_strlen(current->key)
					+ ft_strlen(current->value + 2) * sizeof(char)));
		ft_strcpy(tab[i], current->key);
		tab[i][ft_strlen(current->key)] = '=';
		ft_strcpy(tab[i++] + ft_strlen(current->key) + 1, current->value);
		current = current->next;
	}
	return (tab[i] = NULL, tab);
}
