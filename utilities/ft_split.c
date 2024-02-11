/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:32:33 by mel-jira          #+#    #+#             */
/*   Updated: 2024/02/10 18:42:00 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_count_words(const char *str, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			word++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (word);
}

static	int	ft_world_len(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static	void	ft_freestrings(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
}

static char	**create_string(char **strs, char const *str, char c, int words)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	while (i < words)
	{
		while (str[p] == c)
			p++;
		if (str[p] != c)
		{
			strs[i] = ft_substr(str, p, ft_world_len(&str[p], c));
			if (strs[i] == NULL)
			{
				ft_freestrings(strs);
				free(strs);
				return (NULL);
			}
		}
		while (str[p] != c && str[p] != '\0')
			p++;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**strs;

	if (s == NULL)
		return (NULL);
	words = ft_count_words(s, c);
	strs = (char **)malloc((words + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs = create_string(strs, s, c, words);
	if (strs == NULL)
		return (NULL);
	return (strs);
}
