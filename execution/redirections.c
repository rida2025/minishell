/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:32:54 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/16 21:08:11 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
int check_one_of(char *str)
{
    int i;
    char *tmp =" \'\"$";
    int j = 0;
    i = 0;
    while (str[i])
    {
       j = 0;
       while (tmp[j])
       {
           if(str[i] == tmp[j])
           {
               return (tmp[j]);
           }
           j++;
       }
        i++;
    }
    return 0;
}
char *expandHerdoc(t_env *env_list, char *str)
{
    char *str_hold = str;
    char *tmp1 = NULL;
    char *tmp2 =NULL;
    char *tmp3 =NULL;
    char *hold = NULL;
    char *result = "";
    int cases = 0;
    // char *tmp4 = NULL;
    
    while(str_hold && ft_strchr(str_hold, '$'))
    {
        tmp1 = ft_substr(str_hold, 0, get_index(str_hold, '$'));
        tmp2 = ft_substr(str_hold, get_index(str_hold, '$')+1, ft_strlen(str_hold) - get_index(str_hold, '$'));
        cases = check_one_of(tmp2);
        if(cases != 0)
        {
                tmp3 = ft_substr(tmp2, 0, get_index(tmp2, cases));
                str_hold = ft_substr(tmp2, get_index(tmp2, cases), ft_strlen(tmp2) - get_index(tmp2, cases));
                if(tmp3[0] == '\'' || tmp3[0] == '\"')
                {
                    hold = tmp3;
                    tmp3 =ft_strjoin("$", tmp3);
                    free(hold);
                }
                else{
                    hold = tmp3;
                    tmp3 = ret_val(env_list, tmp3);
                    free(hold);
                }
        }
        else
        {
            tmp3 = ft_strdup(tmp2);
            if(tmp3[0] == '\'' || tmp3[0] == '\"')
                tmp3 =ft_strjoin("$", tmp3);
            else{
                tmp3 = ret_val(env_list, tmp3);
            }
            str_hold = NULL;
        }
        if(tmp1 == NULL)
            tmp1 = ft_strdup("");
        if(tmp3 == NULL)
            tmp3 = ft_strdup("");
        if(result == NULL)
            result = ft_strjoin(tmp1, tmp3);
        else
        {
            hold = result;
            result = ft_strjoin(result, tmp1);
            result = ft_strjoin(result, tmp3);
        }
        free(tmp1);
        free(tmp2);
        if(tmp3 != NULL)
            free(tmp3);
        if(str_hold == NULL)
            break;
    }
    if(str_hold != NULL)
        result = ft_strjoin(result, str_hold);
    return (result);
}

int heredoc(t_env *env_list, char *name , int flag)
{
    int fd[2];
    char *str;
    
    pipe(fd);
    
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strrcmp(name, str))
			break ;
		if(flag == 1)
            str = expandHerdoc(env_list, str);
		write(fd[1], str, ft_strlen(str));
		write(fd[1], "\n", 1);
		free(str);
	}
    return (close(fd[1]),fd[0]);
}

void open_herdocs(t_env *env_list, t_ex *t)
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
                iterate->fd[0] = heredoc(env_list, a->name,a->expand);
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
            }
             if (a->type == 5) //<
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
    t_ex *tmp_it;
    tmp_it = it;
    //print the linked list values
    // while(tmp_it)
    // {
    //     printf("CMD: %s\n", tmp_it->cmd[0]);
    //     tmp_it = tmp_it->next;
    // }
	while (it)
	{
        if(it->cmd[0] == NULL)
        {
            it = it->next;
            continue ;
        }
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
    open_herdocs(env_list, t);
    redirections(t);
    execution(t, env, env_list);
    if(env)
    {
    while(*env)
    {
        free(*env);
        env++;
    }
    // free(env);
        
    }
    //builtins
    //normal cmds
}
