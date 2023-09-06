/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:07:46 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/06 17:05:46 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_type	token_type(char	*content)
{
	if (strcmp(content, "|") == 0)
		return (PIPE);
	else if (strcmp(content, "<") == 0)
		return (REDIR_IN);
	else if (strcmp(content, ">") == 0)
		return (REDIR_OUT);
	else if (strcmp(content, "<<") == 0)
		return (HEREDOC_IN);
	else if (strcmp(content, ">>") == 0)
		return (HEREDOC_OUT);
	else
		return (WORD);
}

void	get_type(t_list	*list)
{
	t_node	*iter;

	iter = list->head;
	while (iter)
	{
		iter->type = token_type(iter->content);
		iter = iter->next;
	}
}
