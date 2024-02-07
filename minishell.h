/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:17:05 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/07 22:15:32 by mel-jira         ###   ########.fr       */
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

status:
0 = normal
1 = inside dquotes
2 = inside sqoutes
*/

//echo "Start" > output.txt | (cat input.txt | grep "pattern" >> output.txt < input.txt sort | awk '{print $2}' > sorted_output.txt) | echo "Done!"


typedef struct s_info
{
	int		i;
	int		flag;
}	t_info;

typedef struct s_token
{
	int					key;
	int					status;
	int					herdoc;
	char				*value;
	struct s_token		*next;
	struct s_token		*previous;
}	t_token;

typedef struct s_parselist
{
	int					key;
	char				*command;
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

typedef struct s_executelist
{
	char					*cmd;
	char					**allcmd;
	int						fdout;
	int						fdin;
	char					*fdoutname;
	char					*fdinname;
	int						heredoc;
	char					*fdheredname;
	struct s_executelist	*next;
}	t_executelist;

typedef struct s_var
{
	int				expand;
	char			*input;
	t_env			*env;
	t_executelist	*cmd;
}	t_var;

void	create_info(t_token **info, int argc, char **argv, char **envp);
//void	execute_input(t_token *info);
void	free_list(t_token **info);
void	free_listx(t_parselist **info);

//structure tools
char	*get_word(char **str);
void	add_node(t_token **info, int token, char *word, int heredoc);

//utilits
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int size);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *str, int fd);
int		ft_isdigit(int c);

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
void	insert_space(t_token **info, char *input, t_info *var, int len);
void	tokenize(t_token **token, char *input);
void	insert_token(t_token **info, int token, char *word, int is_heredoc);
int		quotes_size(char *str, int *i, char c, int *expand);
int		get_size(char *input, int *i, int *expand);
int		get_size2(char *input, int *i);

//parsing tools
int		check_space(char c);
int		check_s_c(char c);

//parsing function
void	add_command(t_parselist **commands, char *cmd, t_info *infox);
void	parser(t_token *infox, t_parselist **commands);
t_info	*add_information(t_info *infox);

//built in
t_env	*get_env(char **envp);
char	*ret_val(t_env *env_list, char *var);

//syntax error functions
int		check_syntax_error(char *str);
int		check_s_dqoute(char *str);
int		check_redirection(t_token *token, t_var *var);
int		check_redirection_front(t_token *token, t_var *var);
int		check_pipes(t_token *token);
int		check_pipes_front(t_token *token);
int		check_pipes_back(t_token *token);
int		pipe_error1(void);
int		pipe_error2(void);
int		pipe_error3(void);
int		redirection_error(void);
int		redirection_error2(void);
int		redirection_error3(char *str);
void	syntax_error(void);
int		exit_status_fun(int exit_status);
int 	check_expand(char *str, t_env *env);
int		check_redirection(t_token *token, t_var *var);
int		help_checking(t_token *token, t_var *var);
int		redirection_error4(void);

//exit status
int		exit_status_fun(int exit_status);

#endif
