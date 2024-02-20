/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:11 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/20 13:43:12 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	err_cmd(char *cmd)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found ", 21);
	write(2, "\n", 1);
	exit(127);
}

char	*my_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '/';
	i++;
	dest[i] = '\0';
	return (dest);
}

char	*search(char **path, char *cmd, int *fd, int *c)
{
	char	*joined;
	char	*filepath;

	filepath = ft_malloc(ft_strlen(path[*c]) + ft_strlen(cmd) + 2);
	my_strcpy(filepath, path[*c]);
	joined = ft_strjoin(filepath, cmd);
	*fd = open(joined, O_RDONLY);
	if (*fd == -1)
	{
		free(filepath);
		free(joined);
		return (NULL);
	}
	return (joined);
}

char	*find_path(char *full_paths, char *cmd)
{
	char	**path;
	int		i;
	int		c;
	int		fd;
	char	*joined;

	init_find_path(&i, &c, &fd);
	if (full_paths == NULL)
		return (cmd);
	if (cmd[i] == '/' || cmd[i] == '.')
		return (cmd);
	path = ft_split(full_paths, ":");
	if (path)
	{
		while (path[i])
			i++;
		while (c++ < i - 1 && fd == -1)
			joined = search(path, cmd, &fd, &c);
		if (fd == -1)
			err_cmd(cmd);
		close(fd);
		return (free(path), joined);
	}
	return (NULL);
}

char	*check_env_path(char **argenv)
{
	char	*env;

	env = "PATH";
	if (argenv == NULL)
		return (NULL);
	while (*argenv && ft_strncmp(*argenv, env, 4) != 0)
		(argenv)++;
	if (*argenv == NULL)
		return (NULL);
	return (*argenv + 5);
}
