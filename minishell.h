/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:17:05 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/15 21:33:27 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>

/*
0=||
0=&&
1=|
2=>
3=<
4=<<
2=` ` || (9>=&&<=13)
2=""
3=''
8=<<
9=$?
10=$
*/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_holyshit
{
	int					position;
	char				*cmd;
	char				*cmdpath;
	int					type;
	struct s_holyshit	*next;
}	t_holyshit;


typedef struct s_word
{
	
}		t_word;

void	create_info(t_holyshit **info, int argc, char **argv, char **envp);
void	insert_data(t_holyshit **info, char *input);
void	execute_input(t_holyshit *info);
void	free_input(t_holyshit *info);

#endif
