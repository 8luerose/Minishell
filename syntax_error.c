/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:51:04 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/05 16:52:43 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_syntax_error(t_list *list)
{
	//check_point: < >, ><, ||, < <
	t_node *tmp;
	t_node *tmp2;

	tmp = list->head;
	while(tmp)
	{
		if (tmp->next)
		{
			tmp2 = tmp->next;
			if (ft_strcmp(tmp->content, "<") == 0 && ft_strcmp(tmp2->content, ">") == 0)
			{
				printf("sytax_error type_1\n");
				exit(1);
			}
			if (ft_strcmp(tmp->content, ">") == 0 && ft_strcmp(tmp2->content, "<") == 0)
			{
				printf("sytax_error type_2\n");
				exit(1);
			}
			if (ft_strcmp(tmp->content, "|") == 0 && ft_strcmp(tmp2->content, "|") == 0)
			{
				printf("sytax_error type_3\n");
				exit(1);
			}
			if (ft_strcmp(tmp->content, "<") == 0 && ft_strcmp(tmp2->content, "<") == 0)
			{
				printf("sytax_error type_4\n");
				exit(1);
			}
			if (ft_strcmp(tmp->content, ">") == 0 && ft_strcmp(tmp2->content, ">") == 0)
			{
				printf("sytax_error type_5\n");
				exit(1);
			}
		}
		tmp = tmp->next;
	}
}