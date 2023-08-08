/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:43:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/08 21:01:28 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_list(t_list *list, t_data *pipeline_list)
{ 
	t_node		*p;
	enum e_type	type;

	p = list->head;
	while (p)
	{
		type = p->type;
		if (type == WORD)
		{
			//명령어(cmd)가 word
			//ls < infile1 cat
			//word인데, Redi 뒤에 있는 게 아니면 무조건! cmd
			//cmd 2차원 포인터에 넣어줘 차례대로
			//어떻게 넣어줄거냐 
			//기존 i 기억하고, 그 다음에 넣어준다, while한번 돌때 i 초기화
			//redirect 나오면 뒤에꺼 같이묶어서 redi에 넣어주고, i++해주고 그 다음부터 다시 순회해주면 됨
			//redirect 나와서 묶어줬으면 p -> next 
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
