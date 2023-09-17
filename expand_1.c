/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 06:00:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/17 12:43:15 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_envp_size(char *content)
{
	int	i;
	int	size;

	i = 0;
	if (content[i + 1] && content[i + 1] == '?')
		return (2);
	if (ft_isalnum(content[i + 1]) || content[i + 1] == '_')
		i++;
	else
		return (-1);
	size = 1;
	while (content[i])
	{
		if (!(ft_isalnum(content[i]) || content[i] == '_'))
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
	{
		free(key);
		return (1);
	}
	return (0);
}

char	*get_env(char *key, t_list *envp)
{
	char	*tmp;
	char	*content;
	t_node	*iter;

	if (key_is_error_stat(key))
		return (ft_itoa(g_stat));
	content = "\0";
	tmp = ft_strdup(key);
	free(key);
	key = ft_strjoin(tmp, "=");
	free(tmp);
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
	free(key);
	return (content);
}
