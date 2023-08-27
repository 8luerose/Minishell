/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:51:40 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/25 18:51:34 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_lstnew(char *content)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->content = ft_strdup(content);
	new->next = NULL;
	new->prev = NULL;
	new->type = 0;   // ㄴㅏ주ㅇ에 고고치치기
	return (new);
}

void	make_head_node(char *content, t_list *list)
{
	t_node	*new;

	new = ft_lstnew(content);
	list->head = new;
	list->tail = new;
}

void	join_node(char *content, t_list *list)
{
	t_node	*new;

	new = ft_lstnew(content);
	new->prev = list->tail;
	(list->tail)->next = new;
	list->tail = new;
}

void	make_node(char *content, t_list *list)
{
	if (list->head == NULL)
		make_head_node(content, list);
	else
		join_node(content, list);
}
