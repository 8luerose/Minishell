/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:41:19 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/11 04:02:23 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax_error(t_list *list)
{
	t_node	*tmp;
	int	prev_type;

	tmp = list->head;
	prev_type = WORD; // 초기값 설정

	while(tmp)
	{
		// 1. 명령어 시작과 끝에 연산자가 오는 경우
		if ((tmp == list->head || tmp->next == NULL) && 
			(tmp->type == PIPE || tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == HEREDOC_IN || tmp->type == HEREDOC_OUT))
		{
			printf("syntax_error at beginning/end\n");
			exit(1);
		}

		// 2. 특정 연산자 조합을 문법 오류로 간주
		if (prev_type == REDIR_IN && tmp->type == PIPE)
		{
			printf("syntax_error with <|>\n");
			exit(1);
		}
		else if (prev_type == REDIR_OUT && tmp->type == PIPE)
		{
			printf("syntax_error with >|<\n");
			exit(1);
		}
		else if (prev_type == HEREDOC_IN && tmp->type == PIPE)
		{
			printf("syntax_error with <<|>>\n");
			exit(1);
		}
		else if (prev_type == HEREDOC_OUT && tmp->type == PIPE)
		{
			printf("syntax_error with >>|<<\n");
			exit(1);
		}
		else if (prev_type == PIPE && (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == HEREDOC_IN || tmp->type == HEREDOC_OUT) && (tmp->next == NULL || tmp->next->type != WORD))
		{
			printf("syntax_error: No target specified after redirection\n");
			exit(1);
		}
		// 3. 연속적인 리다이렉션 처리
		else if ((prev_type == REDIR_IN && tmp->type == REDIR_IN) ||
				 (prev_type == REDIR_OUT && tmp->type == REDIR_OUT) ||
				 (prev_type == HEREDOC_IN && tmp->type == HEREDOC_IN) ||
				 (prev_type == HEREDOC_OUT && tmp->type == HEREDOC_OUT))
		{
			printf("syntax_error with continuous redirections\n");
			exit(1);
		}

		prev_type = tmp->type;
		tmp = tmp->next;
	}
}



// void check_syntax_error(t_list *list)
// {
// 	//check_point: < >, ><, ||, < <
// 	t_node *tmp;
// 	t_node *tmp2;

// 	tmp = list->head;
// 	while(tmp)
// 	{
// 		if (tmp->next)
// 		{
// 			tmp2 = tmp->next;
// 			if (ft_strcmp(tmp->content, "<") == 0 && ft_strcmp(tmp2->content, ">") == 0)
// 			{
// 				printf("sytax_error type_1\n");
// 				exit(1);
// 			}
// 			if (ft_strcmp(tmp->content, ">") == 0 && ft_strcmp(tmp2->content, "<") == 0)
// 			{
// 				printf("sytax_error type_2\n");
// 				exit(1);
// 			}
// 			if (ft_strcmp(tmp->content, "|") == 0 && ft_strcmp(tmp2->content, "|") == 0)
// 			{
// 				printf("sytax_error type_3\n");
// 				exit(1);
// 			}
// 			if (ft_strcmp(tmp->content, "<") == 0 && ft_strcmp(tmp2->content, "<") == 0)
// 			{
// 				printf("sytax_error type_4\n");
// 				exit(1);
// 			}
// 			if (ft_strcmp(tmp->content, ">") == 0 && ft_strcmp(tmp2->content, ">") == 0)
// 			{
// 				printf("sytax_error type_5\n");
// 				exit(1);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }
