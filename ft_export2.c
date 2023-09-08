/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 03:14:38 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/09 06:13:53 by taehkwon         ###   ########.fr       */
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
		{
			if (str[i - 1] == '-')
				return (0);
			break ;
		}
		i++;
	}
	i++;
	if (i == 1)
		exit(1);
	key = ft_strndup(str, i);
	key = ft_strjoin(key, "=");
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
}
