/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:35:43 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/30 10:56:19 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo "hello  $USER " > file | grep h | cat << eof | cat >> file | echo 'done'
int	check_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	check_s_c(char c)
{
	if ((c == '$' || c == '|' || c == '>' || c == '<' || \
		c == '\'' || c == '\"'))
		return (1);
	return (0);
}

int	dcheck_s_c(char *str)
{
	if (!(ft_strncmp(str, ">>", 2)) || !(ft_strncmp(str, "<<", 2)))
		return (2);
	return (0);
}

char	*get_word(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str && (*str)[i])
	{
		if (check_space((*str)[i]) || check_s_c((*str)[i]) \
			|| dcheck_s_c(&(*str)[i]))
		{
			if (dcheck_s_c((*str)))
				i = 2;
			if (i == 0)
				i = 1;
			return (ft_strndup(*str, i));
		}
		i++;
	}
	return (ft_strdup(*str));
}
