/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:17:05 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/14 16:12:04 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <unistd.h>

//none valid symbols after $ sign so don't expand
# define NONE_VALID "$\"'+-./:;<=>@[\\]^`{|}~%#&()*,"
# define STOPNOW "$ |><\"'"
# define EXP "abcdefghijklmnopqrstuvwxyzABCEDFGHIJKLMNOPQRSTUVWXYZ?_"
# define EXP2 "abcdefghijklmnopqrstuvwxyzABCEDFGHIJKLMNOPQRSTUVWXYZ_"
# define EXPANDO "0123456789-_#?"

/*
type:
0 = word
1 = | pipe
2 = " dquote
3 = ' quote
4 = > right redirection
5 = < left redirection
6 = >> right append
7 = << here_doc
8 = $ variable
9 =  is_space 
10 = options
-1 already token

status:
0 = normal
1 = inside dquotes
2 = inside sqoutes
*/



typedef struct s_info
{
	int		i;
	int		flag;
}	t_info;

typedef struct s_token
{
	int					key;
	int					status;
	int					expand;
	char				*value;
	struct s_token		*next;
	struct s_token		*previous;
}	t_token;

typedef struct s_parselist
{
	int					key;
	char				*command;
	int					expand;
	struct s_parselist	*next;
	struct s_parselist	*previous;
}	t_parselist;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exp
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_exp;

typedef struct s_all
{
	t_env	env;
	t_exp	exp;
}	t_all;

typedef struct s_commands
{
	char					*cmd;
	int						key;
	struct s_commands		*next;
}	t_cmd;

typedef struct s_redirections
{
	char					*value;
	int						key;
	int						expand;
	struct s_redirections	*next;
}	t_redirect;

typedef struct s_red
{
	char			*name;
	int				type;
	int				expand;
	struct s_red	*next;
}	t_red;

typedef struct s_main_exec
{
	char				**allcmd;
	int					fd[2];
	t_red				*red;
	struct s_main_exec	*next;
}	t_main_exec;

typedef struct s_var
{
	int				expand;
	char			*input;
	t_env			*env;
	t_main_exec		*cmd;
}	t_var;

//free functions
void	free_list(t_token **info);
void	free_listx(t_parselist **info);
void	free_files(t_red **file);
void	free_redirections(t_redirect **file);
void	free_commands(t_cmd **cmds);
void	free_execution(t_main_exec **cmd);

//structure tools

//utilits
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinx(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *str, int fd);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);

//tokenizing
char	*ft_skip_spaces(char *str);
void	insert_word(t_token **info, char *input, t_info *var, int len);
void	handle_options(t_token **info, char *input, t_info *var, int len);
void	insert_pipe(t_token **info, char *input, t_info *var, int len);
void	insert_quote(t_token **info, char *input, t_info *var, int len);
void	insert_righr(t_token **info, char *input, t_info *var, int len);
void	insert_leftr(t_token **token, char *input, t_info *var, int len);
void	insert_append(t_token **token, char *input, t_info *var, int len);
void	insert_heredoc(t_token **token, char *input, t_info *var, int len);
void	insert_variable(t_token **token, char *input, t_info *var, int len);
void	insert_whitespaces(char *input, t_token **token, t_info *var, int len);
void	tokenize(t_token **token, char *input);
void	insert_token(t_token **info, int token, char *word);

//expanding functions
void	remove_dollar(t_token **token);
void	expand_variables(t_token **token, t_env *env, char *str);
int		there_is_heredoc(t_token *token);
void	reset_expand(t_token *token);
char	*normal_expanding(t_env *env, char *str, int i);
char	*new_advance_expander(char *str, t_env *env);
char	*ret_val(t_env *env_list, char *var);
char	*bringme_new_str(char *str, int *i);
void	set_expanding(t_token **token);
char	*bring_me_expand(char *str, int *i, t_env *env);
char	*get_variable(char *str, int *i);
char	*skipandexpand(char *str, int *i, t_env *env);

//parsing tools
int		check_space(char c);
void	remove_quotes(t_token **token);
void	parse_spaces(t_parselist **parse);

//parsing function
void	name_redirections(t_parselist **parse, t_redirect **redirection);
void	get_commands(t_parselist **parse, t_cmd **commands);
void	put_node(t_redirect **redirection, char *str, int type, int expando);
void	put_nodex(t_cmd **redirection, char *str, int type);
void	insert_node(t_parselist **parse, char *value, int type, int expando);
void	parse_tokens(t_token **token, t_parselist **parse);
t_token	*parse_helper1(t_token *tmp, t_parselist **parse, char *str);

//built in
t_env	*get_env(char **envp);

//syntax error functions
int		check_s_dqoute(char *str);
int		check_tokenizing(t_token **token, t_var *var);
int		check_redirection(t_token *token, t_var *var);
int		check_redirection_front(t_token *token, t_var *var);
int		help_check_redirection(t_var *var, t_token *token, t_token **tmp);
int		check_pipes(t_token *token);
int		check_pipes_front(t_token *token);
int		check_pipes_back(t_token *token);
int		pipe_error1(char *str);
int		pipe_error2(void);
int		redirection_error(void);
int		redirection_error2(void);
int		redirection_error3(char *str);
void	syntax_error(void);
int		exit_status_fun(int exit_status);
int		check_expand(char *str, t_env *env);
int		check_redirection(t_token *token, t_var *var);
int		help_checking(t_token *token, t_var *var);
int		redirection_error4(void);
int		check_ambiguous(char *str, t_env *env);
int		there_is_heredoc(t_token *token);

//execution functions
void		create_execution(t_redirect **red, t_cmd **cmd, t_main_exec **exec);
void		add_node(t_main_exec **execution, char **strs, t_red **redirection);
int			get_size(t_cmd *cmd);
t_redirect	*create_redirection_list(t_redirect *redirect, t_red **red);
void		add_red_node(t_red **redirection, char *str, int key, int expando);
t_cmd		*create_commands_strs(t_cmd *cmds, char ***strs, int size);
// void	add_child_node(t_main_exec **execute, char *command, int key, int exp);
// void	add_files_node(t_main_exec **execute, char *name, int key, int expando);
// void	free_execution(t_main_exec **info);

//exit status
int		exit_status_fun(int exit_status);

//printing structures data
void	print_tokenze(t_token **token);
void	print_parsing(t_parselist **token);
void	print_redirections(t_redirect *redirection);
void	print_commands(t_cmd *commands);
void	print_execution(t_main_exec **execution);

#endif
