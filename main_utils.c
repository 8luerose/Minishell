/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 01:06:34 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/24 01:09:08 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_content(char	*line)
{
	int		i;
	int		size;
	char	*content;

	size = 0;
	while (line[size])
		size++;
	content = (char *)malloc(sizeof(char) * size + 1);
	if (!content)
		exit(1);
	i = 0;
	while (line[i])
	{
		content[i] = line[i];
		i++;
	}
	content[i] = '\0';
	return (content);
}

void	copy_envp(char	**ev, t_envp	*my_envp)
{
	int		i;
	t_flag	flag;
	char	*content;

	i = 0;
	while (ev[i])
	{
		flag.env = 0;
		flag.env_with_quo = 0;
		content = make_content(ev[i]);
		make_node(content, flag, my_envp->envp);
		i++;
	}
}

char	*cut_quo(char *content, int size)
{
	char	*front;
	char	*back;
	char	*new;

	front = ft_substr(content, 0, size);
	back = ft_substr(content, size + 1, ft_strlen(content) - size - 1);
	free(content);
	new = ft_strjoin(front, back);
	return (new);
}

void	delete_quo(t_list *list)
{
	int		i;
	char	quo;
	t_node	*iter;

	iter = list->head;
	while (iter)
	{
		i = 0;
		quo = 0;
		while (iter->content[i])
		{
			if (iter->check != NULL && iter->check[i] == 'F')
			{
				i++;
				continue ;
			}
			if (quo == 0 && (iter->content[i] == '\'' || iter->content[i] == '\"'))
			{
				quo = iter->content[i];
				iter->content = cut_quo(iter->content, i);  // i : 따옴표가 있는 현재 위치
				// i--;
			}
			else if (quo != 0 && iter->content[i] == quo)
			{
				quo = 0;
				iter->content = cut_quo(iter->content, i);
				// i--;
			}
			else
				i++;
		}
		iter = iter->next;
	}
}