/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:17:05 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/14 15:33:54 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>

/*
1=""
2=''
3=;
4=<
5=<<
*/

typedef struct s_holyshit
{
	int					position;
	char				*cmd;
	char				*cmdpath;
	int					type;
	struct s_holyshit	*next;
}	t_holyshit;

void	create_info(t_holyshit **info, int argc, char **argv, char **envp);
void	insert_data(t_holyshit **info, char *input);
void	execute_input(t_holyshit *info);
void	free_input(t_holyshit *info);

#endif
