/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:51:40 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/09 04:51:10 by taehkwon         ###   ########.fr       */
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
	new->type = 0;
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

void	add_mid(char *content, t_node **iter)
{
	t_node	*new;

	new = ft_lstnew(content);
	if ((*iter)->next != NULL)
	{
		new->next = (*iter)->next;
		(*iter)->next->prev = new;
	}
	else
		new->next = NULL;
	new->prev = (*iter);
	(*iter)->next = new;
	(*iter) = new;
}
