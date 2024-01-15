/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:18:17 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/13 12:18:20 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void	put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

int main()
{

	char *cwd;
	if (getcwd(cwd,sizeof(cwd)) != NULL)
		put_str(cwd);
	else
	{
		perror("getcwd() error");
		return 1;
	}
	return 0;
}