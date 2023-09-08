/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 06:00:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/09 06:00:54 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_envp_size(char *content)
{
	int	i;
	int	size;

	i = 0;
	if (content[i + 1] && content[i + 1] == '?')
		return (2);
	if ((content[i + 1] >= 'a' && content[i + 1] <= 'z')
		|| (content[i + 1] >= 'A' && content[i + 1] <= 'Z')
		|| (content[i + 1] >= '0' && content[i + 1] <= '9')
		|| content[i + 1] == '_')
		i++;
	else
		return (-1);
	size = 1;
	while (content[i])
	{
		if (!((content[i] >= 'a' && content[i] <= 'z')
				|| (content[i] >= 'A' && content[i] <= 'Z')
				|| (content[i] >= '0' && content[i] <= '9')
				|| content[i] == '_'))
			break ;
		i++;
		size++;
	}
	return (size);
}

char	*make_key(char *content, int start, int size)
{
	char	*key;

	key = ft_substr(content, start, size);
	return (key);
}

int	key_is_error_stat(char	*key)
{
	if (ft_strcmp(key, "?") == 0)
		return (1);
	return (0);
}

char	*get_env(char *key, t_list *envp)
{
	char	*content;
	t_node	*iter;

	if (key_is_error_stat(key))
		return (ft_itoa(g_stat));
	content = "\0";
	key = ft_strjoin(key, "=");
	iter = envp->head;
	while (iter)
	{
		if (ft_strncmp(key, iter->content, ft_strlen(key)) == 0)
		{
			content = ft_strdup(&iter->content[ft_strlen(key)]);
			break ;
		}
		iter = iter->next;
	}
	return (content);
}

char	*split_expand(char *expand, char **front, t_node **node)
{
	int		i;
	char	**change;

	change = ft_split(expand, ' ');
	i = 0;
	while (change[i])
	{
		if (i == 0)
		{
			free((*node)->content);
			if (ft_strlen((*front)) != 0 && expand[0] == ' ')
			{
				(*node)->content = ft_strdup(*front);
				add_mid(change[i], node);
			}
			else
				(*node)->content = ft_strdup(ft_strjoin((*front), change[i]));
		}
		else
			add_mid(change[i], node);
		i++;
	}
	return ((*node)->content);
}
