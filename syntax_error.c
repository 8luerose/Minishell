/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:41:19 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/17 14:03:09 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_exit(void)
{
	g_stat = 258;
	return (1);
}

int	is_and(char	*content)
{
	char	*and;

	and = ft_strdup("&&");
	if (ft_strcmp(content, and) == 0)
	{
		printf("syntax error `&&'\n");
		free(and);
		return (1);
	}
	free(and);
	return (0);
}

int	syntax_errors(t_node *p, t_list *list)
{
	if (is_and(p->content))
		return (syntax_exit());
	if ((p->next) && p->next->type == HEREDOC_IN && p->type == HEREDOC_IN)
		return (printf("syntax error '<'\n"), syntax_exit());
	if ((p->next) && ((p->next->type == REDIR_IN && p->type == REDIR_IN) || \
		(p->next->type == REDIR_OUT && p->type == REDIR_OUT) || \
		(p->next->type == HEREDOC_OUT && p->type == HEREDOC_OUT) || \
		(p->next->type == PIPE && p->type == PIPE)))
	{
		printf("syntax error '%s%s' \n", p->content, p->next->content);
		return (syntax_exit());
	}
	if ((p->type == REDIR_IN || p->type == REDIR_OUT || \
		p->type == HEREDOC_IN || p->type == HEREDOC_OUT)
		&& (p->next == NULL || (p->next && p->next->type != WORD)))
	{
		printf("syntax error near unexpected token `newline'\n");
		return (syntax_exit());
	}
	if ((p == list->head || p->next == NULL) && p->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (syntax_exit());
	}
	return (0);
}

int	check_syntax_error(t_list *list)
{
	t_node	*p;

	p = list->head;
	while (p)
	{
		if (syntax_errors(p, list))
			return (1);
		p = p->next;
	}
	return (0);
}
