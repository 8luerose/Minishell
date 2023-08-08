/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:43:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/08 20:26:36 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_list(t_list *list)
{ 
	t_node		*p;
	enum e_type	type;

	p = list->head;
	while (p)
	{
		type = p->type;
		if (type == WORD)
		{
			
		}
		else if (type == REDIR_IN && type == REDIR_OUT)
		{

		}
		else if (type == HEREDOC_IN && type == HEREDOC_OUT)
		{

		}
		else if (type == PIPE)
		{

		}
		else
		{

		}
		p = p->next;
	}
}
