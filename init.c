/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:24:58 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/06 17:19:18 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	new_redir->redir = ft_strdup(p->content);
	new_redir->file_name = ft_strdup(p->next->content);
	new_redir->limiter = NULL;
	new_redir->next = NULL;
	return (new_redir);
}

t_envp	*init_new_envp(void)
{
	t_envp	*new_envp;

	new_envp = (t_envp *)malloc(sizeof(t_envp));
	new_envp->ev = NULL;
	new_envp->envp = (t_list *)malloc(sizeof(t_list));
	new_envp->envp->head = NULL;
	new_envp->envp->tail = NULL;
	return (new_envp);
}

t_list	*init_new_list(void)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	new_list->head = NULL;
	new_list->tail = NULL;
	return (new_list);
}
