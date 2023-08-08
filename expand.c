/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:29:09 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/08 14:39:43 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_space(char	*content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	split_node(t_node *iter)
{
	int		i;
	char	**tmp;
	t_flag	flag;
	t_node	*new;

	flag.env = 0;
	flag.env_with_quo = 0;
	tmp = ft_split(iter->content, ' ');
	iter->content = ft_strdup(tmp[0]);
	i = 1;
	while (tmp[i])
	{
		new = ft_lstnew(tmp[i], flag);
		new->prev = iter;
		new->next = iter->next;
		if (iter->next)
			iter->next->prev = new;
		iter->next = new;
		iter = iter->next;
		i++;
	}
}

void	expand_just_envp(t_list	*envp, t_node	*node)
{
	int		i;
	int		quo;
	int		size;
	char	*content;

	quo = 0;
	size = 0;
	content = node->content;
	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			size = check_envp(&content[i]);
			if (size > 0)
			{
				content = change_to_envp(i, size, content, envp);
				i--;
			}
		}
		i++;
	}
	node->content = content;
}

void	expand_with_quo(t_list	*envp, t_node	*node)
{
	int		i;
	int		quo;
	int		size;
	char	*content;

	quo = 0;
	size = 0;
	i = 0;
	content = node->content;
	while (content[i])
	{
		if (content[i] == '\"' && quo == 0)
			quo = 1;
		else if (content[i] == '\"' && quo == 1)
			quo = 0;
		else if (content[i] == '$' && quo == 1)
		{
			size = check_envp(&content[i]);
			if (size > 0)
				content = change_to_envp(i, size, content, envp);
		}
		i++;
	}
	node->content = content;
}

void	expand(t_list	*envp, t_list *list)
{
	t_node	*iter;

	iter = list->head;
	while (iter)
	{
		if (iter->env == 1)
		{
			// 리다이렉션 뒤에 확장 제한 있음. 코드 추가해주기
			expand_just_envp(envp, iter);
			if (have_space(iter->content))
				split_node(iter);
		}
		if (iter->env_with_quo == 1)
			expand_with_quo(envp, iter);
		iter = iter->next;
	}
}
