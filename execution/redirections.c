/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:17:51 by sacharai          #+#    #+#             */
/*   Updated: 2024/02/19 11:46:49 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_one_of(char *str)
{
	int		i;
	char	*tmp;
	int		j;

	j = 0;
	i = 0;
	tmp = " \'\"$";
	while (str[i])
	{
		j = 0;
		while (tmp[j])
		{
			if (str[i] == tmp[j])
				return (tmp[j]);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_ini(char **tmp1, char **tmp2, char **tmp3, char **result)
{
	*result = "";
	*tmp1 = NULL;
	*tmp2 = NULL;
	*tmp3 = NULL;
}

char	*expand_help(char **tmp2, char **str, t_env **env_list)
{
	char	*tmp3;

	*tmp2 = ft_substr(*str, get_index(*str, '$') + 1, \
	ft_strlen(*str) - get_index(*str, '$'));
	if (check_one_of(*tmp2) != 0)
	{
		tmp3 = ft_substr(*tmp2, 0, get_index(*tmp2, \
			check_one_of(*tmp2)));
		*str = ft_substr(*tmp2, get_index(*tmp2, check_one_of(*tmp2)), \
			ft_strlen(*tmp2) - get_index(*tmp2, check_one_of(*tmp2)));
		if (tmp3[0] == '\'' || tmp3[0] == '\"')
			tmp3 = ft_strjoin("$", tmp3);
		else
			tmp3 = ret_val(*env_list, tmp3);
	}
	else
	{
		tmp3 = ft_strdup(*tmp2);
		if (tmp3[0] == '\'' || tmp3[0] == '\"')
			tmp3 = ft_strjoin("$", tmp3);
		else
			tmp3 = ret_val(*env_list, tmp3);
		*str = NULL;
	}
	return (tmp3);
}

char	*expand_herdoc(t_env *env_list, char *str)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*result;

	ft_ini(&tmp1, &tmp2, &tmp3, &result);
	while (str && ft_strchr(str, '$'))
	{
		tmp1 = ft_substr(str, 0, get_index(str, '$'));
		tmp3 = expand_help(&tmp2, &str, &env_list);
		if (tmp1 == NULL)
			tmp1 = ft_strdup("");
		if (tmp3 == NULL)
			tmp3 = ft_strdup("");
		if (result == NULL)
			result = ft_strjoin(tmp1, tmp3);
		else
		{
			result = ft_strjoin(result, tmp1);
			result = ft_strjoin(result, tmp3);
		}
	}
	if (str != NULL)
		result = ft_strjoin(result, str);
	return (result);
}

void	handles(int help)
{
	if (help == SIGINT)
		close(0);
}
