/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:40:06 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/28 12:57:11 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_val(t_env *env_list, char *var)
{
	t_env	*tmp;

	tmp = env_list;
	if (!var)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_command(t_parselist **commands, char *cmd, t_info *infox)
{
	t_parselist	*new_node;
	t_parselist *tmp;

	new_node = malloc(sizeof(t_parselist));
	if (!new_node)
		return ;//edit this later
	new_node->command = cmd;
	new_node->info = add_information(infox);
	new_node->next = NULL;
	new_node->previous = NULL;
	if (!*commands)
		*commands = new_node;
	else
	{
		tmp = *commands;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->previous = tmp;
	}
}

void	parser(t_tokenlist *infox, t_parselist **commands)
{
	t_tokenlist *tmp;
	int			location;
	int			check;

	int i = 0;
	location = 0;
	tmp = infox;
	check = 0;
	while (tmp)
	{
		if (tmp && tmp->info->type == 1)
		{
			printf("pipe\n");
			insert_pipe(tmp, commands, location);
		}
		else if (tmp && tmp->info->type == 4)
		{
			printf("right redirection\n");
			insert_rredirection(tmp, commands, location);
		}
		else if (tmp && tmp->info->type == 5)
		{
			printf("left redirection\n");
			insert_lredirection(tmp, commands, location);
		}
		else if (tmp && tmp->info->type == 6)
		{
			printf("right append\n");
			insert_rdredirection(tmp, commands, location);
		}
		else if (tmp && tmp->info->type == 7)
		{
			printf("here_doc\n");
			insert_ldredirection(tmp, commands, location);
		}
		else if (tmp && tmp->info->type == 8)
		{
			printf("variable\n");
			tmp = insert_variable(tmp, commands, location);
		}
		else if (tmp && tmp->info->status == -1)
		{
			tmp = tmp->next;
			check = 1;
		}
		else
		{
			printf("word\n");
			// printf("and the word=[%s], type=[%d], position=[%d]\n", tmp->word, tmp->info->type, tmp->info->position);
			// printf("and the status=[%d]\n", tmp->info->status);
			// if (tmp)
			// {
			// 	printf("see if its null\n");
			// 	printf("%s\n", tmp->next->word);
			// }
			i++;
			if (i == 10)
				break ;
			tmp = join_words(tmp, commands, location);
			check = 1;
		}
		location++;
		if (tmp && check == 0)
			tmp = tmp->next;
		check = 0;
	}
	printf("parsing was done\n");
}

t_tokenlist	*insert_variable(t_tokenlist *info, t_parselist	**commands, int location)
{
	t_tokenlist	*tmp;
	char		*str;
	t_info		basic;

	tmp = info;
	tmp = tmp->next;
	basic.position = location;
	basic.type = 8;
	basic.status = tmp->info->status;
	str = NULL;
	if (tmp->info->type == 0)
		str = ft_strdup(tmp->word);
	add_command(commands, str, &basic);
	return (tmp);
}

// t_tokenlist	*join_spaces(t_tokenlist *info, t_parselist	**commands, int location)
// {
// 	t_tokenlist	*tmp;
// 	char		*str;
// 	t_info		basic;

// 	basic.position = location;
// 	basic.type = 9;
// 	basic.status = 1;
// 	tmp = info;
// 	str = ft_strdup(" ");
// 	while (tmp)
// 	{
// 		if (tmp && tmp->info->type == 9 && tmp->info->status == 1)
// 		{
// 			tmp = tmp->next;
// 			if (tmp && tmp->info->type == 9 && tmp->info->status == 1)
// 				tmp = tmp->next;
// 			else
// 				break ;
// 		}
// 		else
// 			break ;
// 	}
// 	add_command(commands, str, &basic);
// 	return (tmp);
// }

t_tokenlist	*join_words(t_tokenlist *info, t_parselist **commands, int location)
{
	t_tokenlist	*tmp;
	char		*str;
	t_info		basic;

	basic.position = location;
	basic.type = 0;
	basic.status = 1;
	tmp = info;
	str = ft_strdup("");
	while (tmp)
	{
		if (tmp->info->status == -1)
			tmp = tmp->next;
		else if (tmp && \
			tmp->info->type == 0 || \
			(tmp->info->type != 4 && tmp->info->type != 1 && \
			tmp->info->type != 5 && tmp->info->type != 6 && \
			tmp->info->type != 7 && tmp->info->type != 8))
		{
			str = ft_strjoin(str, tmp->word);
			tmp = tmp->next;
		}
		else
			break ;
	}
	add_command(commands, str, &basic);
	return (tmp);
}

void	insert_pipe(t_tokenlist *info, t_parselist **commands, int location)
{
	t_tokenlist *tmp;
	char		*str;
	t_info		basic;

	basic.position = location;
	basic.type = 1;
	basic.status = 1;
	tmp = info;
	str = ft_strdup(tmp->word);
	add_command(commands, str, &basic);
}

void	insert_rredirection(t_tokenlist *info, t_parselist **commands, int location)
{
	t_tokenlist *tmp;
	char		*str;
	t_info		basic;

	basic.position = location;
	basic.type = 4;
	basic.status = 1;
	tmp = info;
	str = ft_strdup(tmp->word);
	add_command(commands, str, &basic);
}

void	insert_lredirection(t_tokenlist *info, t_parselist **commands, int location)
{
	t_tokenlist *tmp;
	char		*str;
	t_info		basic;

	basic.position = location;
	basic.type = 5;
	basic.status = 1;
	tmp = info;
	str = ft_strdup(tmp->word);
	add_command(commands, str, &basic);
}

void	insert_rdredirection(t_tokenlist *info, t_parselist **commands, int location)
{
	t_tokenlist	*tmp;
	char		*str;
	t_info		basic;

	basic.position = location;
	basic.type = 6;
	basic.status = 1;
	tmp = info;
	str = ft_strdup(tmp->word);
	add_command(commands, str, &basic);
}

void	insert_ldredirection(t_tokenlist *info, t_parselist **commands, int location)
{
	t_tokenlist	*tmp;
	char		*str;
	t_info		basic;

	basic.position = location;
	basic.type = 7;
	basic.status = 1;
	tmp = info;
	str = ft_strdup(tmp->word);
	add_command(commands, str, &basic);
}
