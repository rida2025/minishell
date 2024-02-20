/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:23:19 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 09:26:13 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_the_var(t_var *var)
{
	var->expand = 0;
	var->input = NULL;
	var->env = NULL;
	var->cmd = NULL;
}

void	mini_help(char **str)
{
	if (!(*str))
		hangup_call();
	if (ft_strcmp((*str), ""))
		add_history(*str);
}

void	restore_stdin(int *f_dup)
{
	if (ttyname(0) == NULL)
		if (dup2((*f_dup), STDIN_FILENO) == -1)
			close(*f_dup);
}

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
			return (close(fd[1]), close(fd[0]), -10);
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
