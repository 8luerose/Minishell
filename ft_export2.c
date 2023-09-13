/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 03:14:38 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/11 16:33:18 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char	*str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	i++;
	key = ft_strndup(str, i);
	if (key_check(key))
	{
		free(key);
		return (0);
	}
	free(key);
	key = ft_strndup(str, i + 1);
	return (key);
}

char	*get_value(char	*str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	i++;
	value = ft_strdup(&str[i]);
	return (value);
}

int	only_space(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] != ' ' && value[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	free_replace_content(t_node *node, char *key, char *value)
{
	free(node->content);
	if (only_space(value))
		node->content = ft_strdup(key);
	else
		node->content = ft_strjoin(key, value);
}

void	add_to_tail(t_list *my_envp, char *key, char *value)
{
	char	*new_content;
	t_node	*new_node;

	if (only_space(value))
		new_content = ft_strdup(key);
	else
		new_content = ft_strjoin(key, value);
	new_node = ft_lstnew(new_content);
	my_envp->tail->next = new_node;
	new_node->prev = my_envp->tail;
	my_envp->tail = new_node;
	free(new_content);
}
