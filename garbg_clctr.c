/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbg_clctr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:42:19 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/16 22:31:54 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_grb	**ft_collector(void)
{
	static t_grb	*colctr;
	return (&colctr);
}

t_grb	*ft_lstnew_clctr(void *lst)
{
	t_grb	*new;

	new = malloc(sizeof(t_grb));
    if (!new)
        exit(1);
	new->ptr = lst;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_clctr(t_grb **lst, t_grb *new)
{
	t_grb	*last;

	if (!lst)
		return ;
	last = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	new->next = NULL;
}
