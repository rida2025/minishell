/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:11 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/11 19:26:42 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_cmd(char *cmd)
{
	write(2, " command not found: ", 21);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
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

	filepath = malloc(ft_strlen(path[*c]) + ft_strlen(cmd) + 2);
	if (filepath == NULL)
		return (perror(""), free(path), NULL);
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

	i = 0;
	c = 0;
	fd = -1;
	if (cmd[i] == '/' || cmd[i] == '.')
		return (cmd);
	path = ft_split(full_paths, ':');
	if (path)
	{
		while (path[i])
			i++;
		while (c++ < i - 1 && fd == -1)
			joined = search(path, cmd, &fd, &c);
		if (fd == -1)
			err_cmd(cmd);
		return (free(path), joined);
	}
	return (NULL);
}

char	*check_env_path(char **argenv)
{
	char	*env;

	env = "PATH";
	while (*argenv && ft_strncmp(*argenv, env, 4) != 0)
		(argenv)++;
	if (!*argenv)
	{
		write(2, "> The environment variable PATH not exist\n", 42);
		exit(1);
	}
	return (*argenv + 5);
}