/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:17:05 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/28 09:52:44 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <unistd.h>

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
9 =   is_space 

status:
1 = normal
2 = between dquotes
3 = between quotes
*/

//echo "Start" > output.txt | (cat input.txt | grep "pattern" >> output.txt < input.txt sort | awk '{print $2}' > sorted_output.txt) | echo "Done!"
typedef struct s_info
{
	int		position;
	int		type;
	int		status;
}	t_info;

typedef struct s_tokenlist
{
	char				*word;
	t_info				*info;
	struct s_tokenlist	*next;
	struct s_tokenlist	*previous;
}	t_tokenlist;

typedef struct s_parselist
{
	char				*command;
	t_info				*info;
	struct s_parselist	*next;
	struct s_parselist	*previous;
}	t_parselist;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_executelist
{
	char		**envp;
	t_parselist	*cmds;
}	t_executelist;

void			create_info(t_tokenlist **info, int argc, char **argv, char **envp);
void			insert_data(t_tokenlist **info, char *input);
//void	execute_input(t_tokenlist *info);
void			free_list(t_tokenlist **info);
void			free_listx(t_parselist **info);

//structure tools
char			*get_word(char **str);
void			add_node(t_tokenlist **info, char *nword, int nposition);

//parsing tools
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, int size);
char			*ft_strjoin(char const *s1, char const *s2);
int				check_space(char c);
int				check_s_c(char c);
size_t			ft_strlen(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strchr(const char *s, int c);

//parsing function
void			add_command(t_parselist **commands, char *cmd, t_info *infox);
void			parser(t_tokenlist *infox, t_parselist **commands);
t_tokenlist		*join_spaces(t_tokenlist *info, t_parselist	**commands, int location);
t_tokenlist		*join_words(t_tokenlist *info, t_parselist **commands, int location);
void			insert_pipe(t_tokenlist *info, t_parselist **commands, int location);
void			insert_rredirection(t_tokenlist *info, t_parselist **commands, int location);
void			insert_lredirection(t_tokenlist *info, t_parselist **commands, int location);
void			insert_rdredirection(t_tokenlist *info, t_parselist **commands, int location);
void			insert_ldredirection(t_tokenlist *info, t_parselist **commands, int location);
t_tokenlist		*insert_variable(t_tokenlist *info, t_parselist	**commands, int location);
t_info			*add_information(t_info *infox);

//built in
t_env			*get_env(char **envp);
char			*ret_val(t_env *env_list, char *var);

//repair
void			repair(t_parselist **main, t_env *env);

//error checking //this is for double and single quote only
int				check_error(char *str);

#endif
