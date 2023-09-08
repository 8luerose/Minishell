/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:21:20 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/09 06:12:47 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*process_word(t_node *p, t_data *new_data)
{
	if (!p)
		return (NULL);
	if (p->content && ft_strlen(p->content) > 0)
		append_cmd(new_data, p->content);
	p = p->next;
	return (p);
}

t_node	*process_redir(t_node *p, t_data *new_data)
{
	append_redir(new_data, p);
	p = p->next;
	if (!p || (p->type != WORD))
	{
		printf("ERROR: NO WORD after redirection\n");
		free_pipeline(new_data);
		exit(1);
	}
	p = p->next;
	return (p);
}

void	connect_new_data(t_data **pipe_data, t_data *new_data)
{
	t_data	*tmp;

	if (!*pipe_data)
	{
		*pipe_data = new_data;
	}
	else
	{
		tmp = (*pipe_data);
		while (tmp && tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new_data;
	}
}

void	get_list(t_list *list, t_data **pipeline_list)
{
	t_node	*p;
	t_data	*new_data;

	new_data = init_new_data();
	p = list->head;
	while (p)
	{
		if (p->type == WORD)
			p = process_word(p, new_data);
		else if (p->type == REDIR_IN || p->type == REDIR_OUT \
			|| p->type == HEREDOC_IN || p->type == HEREDOC_OUT)
			p = process_redir(p, new_data);
		else if (p->type == PIPE)
		{
			connect_new_data(pipeline_list, new_data);
			new_data = init_new_data();
			p = p->next;
		}
		else
			p = p->next;
	}
	if (new_data->cmd_line || new_data->redir)
		connect_new_data(pipeline_list, new_data);
	else
		free_pipeline(new_data);
}
