/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:17:05 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/17 21:10:34 by sacharai         ###   ########.fr       */
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

typedef struct s_tokenlist
{
	int					position;
	char				*word;
	int					type;
	int					status;
	struct s_tokenlist	*next;
	struct s_tokenlist	*previous;
}	t_tokenlist;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

void	create_info(t_tokenlist **info, int argc, char **argv, char **envp);
void	insert_data(t_tokenlist **info, char *input);
//void	execute_input(t_tokenlist *info);
void	free_list(t_tokenlist **info);

//structure tools
char	*get_word(char **str);
void	add_node(t_tokenlist **info, char *nword, int nposition);

//parsing tools
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int size);
int		check_space(char c);
int		check_s_c(char c);
size_t	ft_strlen(const char *s);

#endif
