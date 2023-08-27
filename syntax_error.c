/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:41:19 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/27 14:42:52 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 원본 코드
// void	check_syntax_error(t_list *list)
// {
// 	t_node	*p;
// 	int		prev_type;

// 	prev_type = 0;
// 	p = list->head;
// 	while (p)
// 	{
// 		// 1. 명령어 시작과 끝에 파이프가 오는 경우 |
// 		if ((p == list->head || p->next == NULL) && (p->type == PIPE))
// 		{
// 			printf("syntax_error (|) at beginning or end\n");
// 			exit(1);
// 		}
// 		if (prev_type == PIPE &&						//| > ' ' or | > '<'
// 				(p->type == REDIR_IN || p->type == REDIR_OUT || p->type == HEREDOC_IN || p->type == HEREDOC_OUT) 
// 				&& (p->next == NULL || p->next->type != WORD))
// 		{
// 			printf("syntax_error: No WORD after redirection\n");
// 			exit(1);
// 		}
// 		// 3. 연속해서 리다이렉션과 파이프 나오는 경우 < <,> >(1차 토큰 기준), <<<<,>>>>
// 		else if ((prev_type == REDIR_IN && p->type == REDIR_IN) ||
// 				 (prev_type == REDIR_OUT && p->type == REDIR_OUT) ||
// 				 (prev_type == HEREDOC_IN && p->type == HEREDOC_IN) ||
// 				 (prev_type == HEREDOC_OUT && p->type == HEREDOC_OUT) ||
// 				 (prev_type == PIPE && p->type == PIPE))
// 		{
// 			printf("syntax_error (< <,> >), (<<<<,>>>>), (||)\n");
// 			exit(1);
// 		}
// 		prev_type = p->type;
// 		p = p->next;
// 	}
// }

int	syntax_errors(int prev_type, t_node *p, t_list *list)
{
	(void)prev_type;
	if ((p == list->head || p->next == NULL) && p->type == PIPE)
	{
		printf("syntax_error (|) at beginning or end\n");
		stat = 258;
		return (1);
	}
	if ((p->type == REDIR_IN || p->type == REDIR_OUT || p->type == HEREDOC_IN || p->type == HEREDOC_OUT) && 
		(p->next == NULL || p->next->type != WORD))
	{
		printf("syntax_error: No WORD after redirection\n");
		stat = 258;
		return (1);
	}
	// if ((prev_type == REDIR_IN && p->type == REDIR_IN) ||
	// 	(prev_type == REDIR_OUT && p->type == REDIR_OUT) ||
	// 	(prev_type == HEREDOC_IN && p->type == HEREDOC_IN) ||
	// 	(prev_type == HEREDOC_OUT && p->type == HEREDOC_OUT) ||
	// 	(prev_type == PIPE && p->type == PIPE))
	// if ((prev_type == ))
	// {
	// 	printf("syntax_error (< <,> >), (<<<<,>>>>), (||)\n");
	// 	stat = 258;
	// 	return (1);
	// }
	return (0);
}

/**
 * pipe pipe
 * redir redir
 * redir pipe
*/

int	check_syntax_error(t_list *list)
{
	t_node	*p;
	int		prev_type;

	prev_type = 0;
	p = list->head;
	while (p)
	{
		if (syntax_errors(prev_type, p, list))
			return (1);
		prev_type = p->type;
		p = p->next;
	}
	return (0);
}
