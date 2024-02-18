/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:23:19 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/18 19:41:37 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	her_help(int *fd, char *str)
{
	write(fd[1], str, ft_strlen(str));
	free(str);
	write(fd[1], "\n", 1);
}

int	heredoc(t_env *env_list, char *name, int flag)
{
	int		fd[2];
	char	*str;
	char	*tmp;

	pipe(fd);
	signal(SIGINT, handles);
	while (1)
	{
		str = readline("> ");
		if (!str)
			return (close(fd[1]), -10);
		if (!ft_strrcmp(name, str))
		{
			free(str);
			break ;
		}
		if (flag == 1)
		{
			tmp = expand_herdoc(env_list, str);
			free(str);
			str = tmp;
		}
		her_help(fd, str);
	}
	return (close(fd[1]), fd[0]);
}
