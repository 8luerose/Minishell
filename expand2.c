/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:30:51 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 16:46:43 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_envp(char	*content)
{
	int		i;
	char	*new;

	i = 0;
	if ((content[i + 1] >= 'a' && content[i + 1] <= 'z')
		|| (content[i + 1] >= 'A' && content[i + 1] <= 'Z')
		|| (content[i + 1] >= '0' && content[i + 1] <= '9'))
		i++;
	else
		return (-1);
	while (content[i])
	{
		if (!((content[i] >= 'a' && content[i] <= 'z')
				|| (content[i] >= 'A' && content[i] <= 'Z')
				|| (content[i] >= '0' && content[i] <= '9')))
			break ;
		i++;
	}
	new = ft_substr(content, 1, i - 1);
	return (i);
}

char	*get_env(char *key, t_list *envp)
{
	char	*content;
	t_node	*iter;

	content = NULL;
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

char	*cut_front(int start, char *content)
{
	int		i;
	char	*tmp1;

	i = 0;
	while (i < start)
		i++;
	tmp1 = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (i < start)
	{
		tmp1[i] = content[i];
		i++;
	}
	tmp1[i] = '\0';
	return (tmp1);
}

char	*cut_back(int start, int size, char *content)
{
	int		i;
	int		j;
	char	*tmp2;

	i = start + size;
	while (content[i])
	{
		i++;
	}
	tmp2 = (char *)malloc(sizeof(char) * i + 1);
	j = 0;
	i = start + size;
	while (content[i])
	{
		tmp2[j] = content[i];
		j++;
		i++;
	}
	tmp2[j] = '\0';
	return (tmp2);
}

char	*change_to_envp(int start, int size, char *content, t_list *envp)
{
	char	*front;
	char	*back;
	char	*change;
	char	*new;

	front = cut_front(start, content);
	back = cut_back(start, size, content);
	change = get_env(ft_substr(content, start + 1, size - 1), envp);
	if (change)
	{
		new = ft_strjoin(front, change);
		new = ft_strjoin(new, back);
	}
	else
		new = ft_strjoin(front, back);
	return (new);
}
