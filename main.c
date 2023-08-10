/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:51:22 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/11 05:19:24 by taehkwon         ###   ########.fr       */
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

// void	minishell(char *input, t_list	*my_envp)
void	minishell(char *input)
{
	t_list	*list;
	t_data	*pipe_parsing;
	t_node 	*test;

	list = (t_list *)malloc(sizeof(t_list));
	list->head = NULL;
	list->tail = NULL;
	get_token(input, list);
	get_type(list);
	check_syntax_error(list);  // syntax 에러
	// expand(my_envp, list);
	
	pipe_parsing = NULL;
	get_list(list, &pipe_parsing);		//1차 토큰화 -> 파이프 단위로 나눔

	print_type(list);					//타입만 확인
	print_result_test(pipe_parsing);	//2차 파싱 잘 구분되었는지 테스트 출력
	print_result(pipe_parsing);			//2차 파싱 결과물 출력
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
			// minishell(input, my_envp);
			minishell(input);
			add_history(input);
		}
	}
	free(input);
	return (0);
}
// gcc -lreadline *.c libft.a -g -fsanitize=address 이걸로 컴파일 해!