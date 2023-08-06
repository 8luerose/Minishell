/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:51:22 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 19:25:22 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char *input)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	list->head = NULL;
	list->tail = NULL;

	get_token(input, list);
	// expand();
	check_syntax_error(list);
	// get_list();
	// get_group_token(list);
	
	t_node *s;
	s = list->head;
	while (s)
	{
		printf("---------------------\n");
		printf("cmd: %s \n env: %d \n env_with_quo: %d\n", s->content, s->env, s->env_with_quo);
		s = s->next;
	}
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("💭 : ");
		if (input)
		{
			minishell(input);
			add_history(input);
		}
	}
	free(input);
	return (0);
}
