/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_ex_get_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 02:56:15 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/09 02:56:31 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	get_list(t_list *list, t_data *pipeline_list)
// { 
// 	t_node		*p;
// 	enum e_type	type;

// 	p = list->head;
// 	while (p)
// 	{
// 		type = p->type;
// 		if (type == WORD)
// 		{
// 			//명령어(cmd)가 word
// 			//ls < infile1 cat 나올 수도 있음
// 			//word인데, Redirection 뒤에 있는 게 아니면 무조건! cmd
// 			//cmd 2차원 포인터에 넣어줘 차례대로
// 			//그러니까 Redirection과 바로 뒤에는 한 묶음, 나머지는 모두 cmd가 되는거라고 생각
// 			//어떻게 넣어줄거냐 
// 			//기존 i 기억하고, 그 다음에 넣어준다, while한번 돌때 i 초기화
// 			//redirect 나오면 뒤에꺼 같이묶어서 redi에 넣어주고, i++해주고 그 다음부터 다시 순회해주면 됨
// 			//redirect 나와서 묶어줬으면 p -> next 
// 		}
// 		else if (type == REDIR_IN && type == REDIR_OUT)
// 		{
			
// 		}
// 		else if (type == HEREDOC_IN && type == HEREDOC_OUT)
// 		{

// 		}
// 		else if (type == PIPE)
// 		{

// 		}
// 		else
// 		{

// 		}
// 		p = p->next;
// 	}
// }