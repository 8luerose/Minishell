/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:41:19 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 12:41:29 by seojchoi         ###   ########.fr       */
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
