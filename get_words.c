/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:35:43 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/15 21:59:36 by mel-jira         ###   ########.fr       */
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
	!(ft_strcmp(&c, ">>")) || !(ft_strcmp(&c, "<<")) || \
	c == '\'' || c == '\"'))
		return (1);
	return (0);
}

char	*skip_spaces(char *str)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (str && str[i])
	{
		if ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
			i++;
		else
			break ;
	}
	tmp = ft_strdup(str + i);
	free(str);
	return (tmp);
}

char	*get_word(char **str)
{
	int		i;

	i = 0;
	//*str = skip_spaces(*str);
	while (*str && (*str)[i])
	{
		if (check_space((*str)[i]) || check_s_c((*str)[i]))
		{
			if (i == 0)
				i = 1;
			return (ft_strndup(*str, i));
		}
		i++;
	}
	return (*str);
}
