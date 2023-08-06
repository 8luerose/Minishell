/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:51:22 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 20:25:20 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**copy_envp(char **ev)
// {
// 	int		i;
// 	int		j;
// 	int		size;
// 	char	**my_envp;

// 	size = 0;
// 	while (ev[size])
// 		size++;
// 	my_envp = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (!my_envp)
// 		exit(1);
// 	i = 0;
// 	while (ev[i])
// 	{
// 		size = 0;
// 		while (ev[i][size])
// 			size++;
// 		my_envp[i] = (char *)malloc(sizeof(char) * (size + 1));
// 		if (!my_envp)
// 			exit(1);
// 		j = 0;
// 		while (ev[i][j])
// 		{
// 			my_envp[i][j] = ev[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (my_envp);
// }

char	*make_content(char	*line)
{
	int		i;
	int		size;
	char	*content;

	size = 0;
	while (line[size])
		size++;
	content = (char *)malloc(sizeof(char) * size + 1);
	if (!content)
		exit(1);
	i = 0;
	while (line[i])
	{
		content[i] = line[i];
		i++;
	}
	return (content);
}

void	copy_envp(char	**ev, t_list	*my_envp)
{
	int		i;
	t_flag	flag;
	char	*content;

	i = 0;
	while (ev[i])
	{
		flag.env = 0;
		flag.env_with_quo = 0;
		content = make_content(ev[i]);
		make_node(content, flag, my_envp);
		i++;
	}
}

void	minishell(char *input, t_list	*my_envp)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	list->head = NULL;
	list->tail = NULL;
	get_token(input, list);
	expand(my_envp, list);
	// type
	// check_syntax_error(list);  // syntax 에러
	// get_list();
	
	t_node *s;
	s = list->head;
	while (s)
	{
		printf("%s\n", s->content);
		s = s->next;
	}
}

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_list	*my_envp;

	ac = 0;
	av = 0;
	my_envp = (t_list *)malloc(sizeof(t_list));
	my_envp->head = NULL;
	my_envp->tail = NULL;
	copy_envp(ev, my_envp);
	while (1)
	{
		input = readline("💭 : ");
		if (input)
		{
			minishell(input, my_envp);
			add_history(input);
		}
	}
	free(input);
	return (0);
}
