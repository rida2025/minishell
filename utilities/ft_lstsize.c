/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:59:37 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/18 15:13:13 by mel-jira         ###   ########.fr       */
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
