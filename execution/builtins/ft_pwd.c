/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:47:47 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/14 06:17:32 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		ft_putstr_fd(buffer, 1);
		return (0);
	}
	else
		perror("getcwd");
}
