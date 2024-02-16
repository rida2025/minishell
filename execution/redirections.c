/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:32:54 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/16 23:04:11 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


char	*generate_name(void)
{
	static int		i;
	char			*str;

	if (i == 0)
		i = 554;
	str = ft_itoa(i);
	// if (-2147483648)
	// 	exit(1); 
	while (access(str, F_OK) == 0 && i > 0)
	{
		free(str);
		i++;
		str = ft_itoa(i);
		if (!str)
			exit(1);
	}
	if (i < 0)
		return (free(str), NULL);
	return (str);
}
int heredoc(char *name)
{
    char *str;
    int fd[2];
    str = generate_name();
    if (!str)
		exit(1);//rare case
   fd[0] = open (str, O_RDWR | O_CREAT);
   fd[1] = open (str, O_RDWR | O_CREAT);
   
    unlink(str);
    free(str);
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strrcmp(name, str))
			break ;
		// if (type == TYPE_HERE_DOC)
		// 	str = expand_heredoc_line(str);
		write(fd[0], str, ft_strlen(str));
		write(fd[0], "\n", 1);
		free(str);
	}
    return (close(fd[0]),fd[1]);
}

void open_herdocs(t_ex *t)
{

    t_ex *iterate;
    iterate = t;
    t_red *a;
    while (iterate)
    {
        a = iterate->red;
        while (a)
        {
            if (a->type == 7)
            {
                a->type = heredoc(a->name) - 1500000;
            }
              a = a->next;
        }
        iterate = iterate->next;
    }
}

void redirections(t_ex *t)
{
    t_ex *iterate;
    iterate = t;
    t_red *a;
    while (iterate)
    {
        a = iterate->red;
        while (a)
        {
            if (a->type == 7) //heredoc
            {
                if (iterate->fd[0] != -1)
                    close(iterate->fd[0]);
                iterate->fd[0] = a->type + 1500000;
            }
            else if (a->type == 5) //<
            {
                if (iterate->fd[0] != -1)
                    close(iterate->fd[0]);
                iterate->fd[0] = open(a->name, O_RDONLY, 0777);
                if (iterate->fd[0] == -1)
                {
                    write(2, "minishell: ", 12);
	                write(2, a->name, ft_strlen(a->name));
	                write(2, ": No such file or directory", 28);
	                write(2, "\n", 1);
                    iterate->fd[0] = -2;
                    
                    return ;
                }
            }
            else if (a->type == 6)// >>
            {
                if (iterate->fd[1] != -1)
                    close(iterate->fd[1]);
                iterate->fd[1] = open(a->name, O_RDWR | O_CREAT | O_APPEND, 0777);
                if (iterate->fd[1] == -1)
                {
                    write(2, "minishell: ", 12);
	                write(2, a->name, ft_strlen(a->name));
	                write(2, ": No such file or directory", 28);
	                write(2, "\n", 1);
                    return ;
                }
            }
            else if(a->type == 4)//>
            {
                if (iterate->fd[1] != -1)
                    close(iterate->fd[1]);
                iterate->fd[1] = open(a->name, O_RDWR | O_CREAT | O_TRUNC, 0777);
                if (iterate->fd[1] == -1)
                {
                    write(2, "minishell: ", 12);
	                write(2, a->name, ft_strlen(a->name));
	                write(2, ": No such file or directory", 28);
	                write(2, "\n", 1);
                    return ;
                }  
            }
            a = a->next;
        }
        iterate = iterate->next;
    }
}


// char	**path(void)
// {
// 	const char	*path;
// 	char		**paths;

// 	path = ft_getenv("PATH");
// 	if (!path)
// 		path = gl.default_env[1];
// 	if (!path && !*gl.default_env[1])
// 		return (0);
// 	paths = ft_split(path + 5, ':');
// 	if (!paths)
// 		ft_error(1, "malloc ");
// 	return (paths);
// }

// char	*cmd_path(char **paths, char *cmd, char *tmp, char *str)
// {
// 	int		i;

// 	i = -1;
// 	if (!paths && cmd && cmd[0] == '/')
// 		return (cmd);
// 	if (!paths || !cmd || (ft_strchr(cmd, '/') && access(cmd, F_OK)))
// 		return (0);
// 	if ((ft_strchr(cmd, '/') && !access(cmd, F_OK)))
// 		return (cmd);
// 	while (paths[++i])
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		if (!tmp)
// 			return (0);
// 		str = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		tmp = 0;
// 		if (!str)
// 			return (0);
// 		if (!access(str, F_OK))
// 			return (str);
// 		free(str);
// 	}
// 	return (0);
// }

void	execution(t_ex *t, char **env, t_env *env_list)
{
    t_ex	*it;
    int		pid;
    int		fd[2];
    char	*path;
    int		i;
   // int		red[2];
    char	*full_path;

    fd[0] = -1;
    fd[1] = -1;
	it = t;
	i = 0;
    int tmp = -1;
	while (it)
	{
		if (it->next)
		{
			if (i == 0)
			{
				pipe(fd);
				if (it->fd[1] == -1)
				    it->fd[1] = fd[1];
                else
                    close(fd[1]);
            }
			else
			{
                close(tmp);
				if (it->fd[0] == -1)
                {
					it->fd[0] = fd[0];
                    tmp = fd[0];
                }
                else
                {
                    close(fd[0]);
                    tmp = -1;
                }
                close (fd[1]);
				pipe(fd);
				if (it->fd[1] == -1)
					it->fd[1] = fd[1];
                else
                    close(fd[1]);
			}
		}
		else
		{
            close(tmp);
			if (it->fd[0] == -1)
				it->fd[0] = fd[0];
            else
                close(fd[0]);
            if (fd[1] != 1)
			 close(fd[1]);
		}
        if (!it->next && i == 0 && is_builtin(it))
        {
            if (it->fd[0] != 0)
            {
                fd[0] = dup(0);
                dup2(it->fd[0], 0);
                close(it->fd[0]);
            }
            if (it->fd[1] != 1)
            {
                fd[1] = dup(1);
                dup2(it->fd[1],1);
                close(it->fd[1]);
            }
            exec_builtin(it->cmd, env_list);
            if (fd[0] != -1)
            {
                dup2(fd[0],0);
                close(fd[0]);
            }
            if (fd[1] != -1)
            {
                dup2(fd[1],1);
                close(fd[1]);
            }
            i++;
            it = it->next;
            continue ;
        }
		pid = fork();
		if (!pid)
		{
            if (it->fd[0] == -2)
                exit(1);
            if (fd[1] != 1 && (it->fd[1] != fd[1]))
                close(fd[1]);
            if (fd[0] != 0 && (it->fd[0] != fd[0]))
                close(fd[0]);
			if ((it->fd[1] != -1) && (it->fd[1] != 1))
			{
				dup2(it->fd[1], 1);
				close(it->fd[1]);
			}
			if (it->fd[0] != -1 && it->fd[0] != 0)
			{
				dup2(it->fd[0], 0);
				close(it->fd[0]);
			}
			//dup
			if (is_builtin(it))
            {
				exec_builtin(it->cmd, env_list);
                exit(0);
            }
            else
			{
				full_path = check_env_path(env);
				path = find_path(full_path, it->cmd[0]);
               
                execve(path, it->cmd, env);
                exit_status_fun(127);
			}
		}
		i++;
		it = it->next;
        // t = t->next;
	}
    if ( fd[0] != 0)
     close(fd[0]);
    while (waitpid(-1, 0, 0) != -1)
        ;
}

void redirect(t_ex *t, t_env *env_list)
{
    char	**env;
    //first step is to handle heredoc 
    // we need to iterate over our linked list to open the herdcs
    env = list_to_tab(env_list);
    open_herdocs(t);
    redirections(t);
    execution(t, env, env_list);
    //builtins
    //normal cmds
}
