/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:59:37 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/12 03:39:37 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_ex *lst)
{
	int		count;
	t_ex	*tmp;

	count = 0;
	tmp = (t_ex *)lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}