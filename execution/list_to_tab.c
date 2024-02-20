/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 03:21:43 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 12:32:51 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_last_cmd(int i)
{
	static int	last;

	if (i == -1)
		return (last);
	last = i;
	return (last);
}

void	*ft_malloc(size_t len)
{
	void	*ptr;

	ptr = malloc(len);
	if (!ptr)
		exit(1);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(ptr));
	return (ptr);
}

int	len_list(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**list_to_tab(t_env *env_list)
{
	t_env	*current;
	char	**tab;
	int		i;

	i = 0;
	current = env_list;
	tab = (char **)ft_malloc((len_list(env_list) + 1) * sizeof(char *));
	current = env_list;
	while (current != NULL)
	{
		if (current->value)
		{
			tab[i] = (char *)ft_malloc(((ft_strlen(current->key) + \
					ft_strlen(current->value) + 2) * sizeof(char)));
			ft_strcpy(tab[i], current->key);
			tab[i][ft_strlen(current->key)] = '=';
			ft_strcpy(tab[i++] + ft_strlen(current->key) + 1, current->value);
		}
		current = current->next;
	}
	return (tab[i] = NULL, tab);
}
