/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:51:40 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/11 04:56:29 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_lstnew(char *content, t_flag flag)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->content = ft_strdup(content);
	new->env = flag.env;
	new->env_with_quo = flag.env_with_quo;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	make_head_node(char *content, t_flag flag, t_list *list)
{
	t_node	*new;

	new = ft_lstnew(content, flag);
	list->head = new;
	list->tail = new;
}

void	join_node(char *content, t_flag flag, t_list *list)
{
	t_node	*new;

	new = ft_lstnew(content, flag);
	new->prev = list->tail;
	(list->tail)->next = new;
	list->tail = new;
}

void	make_node(char *content, t_flag flag, t_list *list)
{
	if (list->head == NULL)
		make_head_node(content, flag, list);
	else
		join_node(content, flag, list);
}

t_data	*init_new_data(void)
{
	t_data	*new_data;

	new_data = (t_data *)malloc(sizeof(t_data));
	new_data->cmd_line = NULL;
	new_data->redir = NULL;
	new_data->next = NULL;
	return (new_data);
}

t_redir	*init_new_redir(t_node *p)
{
	t_redir *new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	new_redir->redir = ft_strdup(p->content);
    new_redir->file_name = ft_strdup(p->next->content);
    new_redir->next = NULL;
	return (new_redir);
}

    