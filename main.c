/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:51:22 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/22 17:35:02 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	content[i] = '\0';
	return (content);
}

void	copy_envp(char	**ev, t_envp	*my_envp)
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
		make_node(content, flag, my_envp->envp);
		i++;
	}
}

char	*cut_quo(char *content, int size)
{
	char	*front;
	char	*back;
	char	*new;

	front = ft_substr(content, 0, size);
	back = ft_substr(content, size + 1, ft_strlen(content) - size - 1);
	free(content);
	new = ft_strjoin(front, back);
	return (new);
}

void	delete_quo(t_list *list)
{
	int		i;
	char	quo;
	t_node	*iter;

	iter = list->head;
	while (iter)
	{
		i = 0;
		quo = 0;
		while (iter->content[i])
		{
			if (iter->check != NULL && iter->check[i] == 'F')
			{
				i++;
				continue ;
			}
			if (quo == 0 && (iter->content[i] == '\'' || iter->content[i] == '\"'))
			{
				quo = iter->content[i];
				iter->content = cut_quo(iter->content, i);  // i : 따옴표가 있는 현재 위치
				// i--;
			}
			else if (quo != 0 && iter->content[i] == quo)
			{
				quo = 0;
				iter->content = cut_quo(iter->content, i);
				// i--;
			}
			else
				i++;
		}
		iter = iter->next;
	}
}

void	minishell(char *input, t_envp *my_envp)
{
	t_list	*list;
	t_data	*pipe_parsing;

	list = init_new_list();
	if (strcmp(input, "exit") == 0)		// "exit" 명령 처리
    {
        free(list);
        free(input);
        exit(0);
    }
	get_token(input, list);
	get_type(list);
	check_syntax_error(list);
	expand(my_envp->envp, list);
	delete_quo(list);
	pipe_parsing = NULL;
	get_list(list, &pipe_parsing);
//////////////////////////////////////
	// print_type(list);
	// print_result_test(pipe_parsing);
	// print_result(pipe_parsing);
//////////////////////////////////////
	execute(pipe_parsing, my_envp);
	// printf("stat: %d\n", stat);
}

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_envp	*my_envp;

	set_terminal_print_off();			// ^C 출력 방지
	ac = 0;
	av = 0;
	my_envp = init_new_envp();
	copy_envp(ev, my_envp);
	while (1)
	{
		signal(SIGINT, handler_sigint);		// Ctrl + C
		signal(SIGQUIT, SIG_IGN);
		stat = 0;
		input = readline("bash: ");
		if (input)						// 입력(문자열)이 있으면 명령 처리
		{
			minishell(input, my_envp);
			add_history(input);
		}
		else 							// ctrl + d (EOF) 입력하면 NULL들어온다
           handler_sigterm();
		free(input);
	}
	set_terminal_print_on();			// ^C 출력 방지끔
	return (0);
}
//맥 클러스터
//gcc -L/Users/taehkwon/.brew/opt/readline/lib -lreadline -I/Users/taehkwon/.brew/opt/readline/include *.c libft.a -g -fsanitize=address

//맥 개인 맥북
//gcc -L/opt/homebrew/opt/readline/lib -l readline -I/opt/homebrew/opt/readline/include *.c libft.a -g -fsanitize=address

//시그널 보내면 부모일때는 무시하고 자식 프로세스일때 시그널 처리

//부모일 때(pid ==0 전일때) signal(SIGINT,SIG_IGN),
//if (pid == 0) 뜨는 순간 signal 처리를 해준다