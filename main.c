/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:51:22 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/24 05:40:13 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char *input, t_envp *my_envp)
{
	t_list	*list;
	t_data	*pipe_parsing;

	stat = 0;
	if (*input)
		add_history(input);					// main에 있던 add_history()를 minishell()로 옮김
	list = init_new_list();
	cmd_exit(input, list);					// "exit" 명령 처리
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

	set_terminal_print_off();				// ^C 출력 방지
	(void)ac;
	(void)av;
	my_envp = init_new_envp();
	copy_envp(ev, my_envp);
	while (1)
	{
		signal(SIGINT, handler_sigint);		// Ctrl + C
		signal(SIGQUIT, SIG_IGN);
		input = readline("bash: ");
		if (input)							// 입력(문자열)이 있으면 명령 처리
			minishell(input, my_envp);
		else 								// ctrl + d (EOF) 입력하면 NULL들어온다
           handler_sigterm();
		free(input);
	}
	return (stat);
}

//명세서
//시그널 보내면 부모일때는 무시하고 자식 프로세스일때 시그널 처리

//부모일 때(pid ==0 전일때) signal(SIGINT,SIG_IGN),
//if (pid == 0) 뜨는 순간 signal 처리를 해준다

//main 내 함수 몇가지 minishell, main_utils.c로 이동 
//waitpid 수정, signal 수정
//too many file moved to other file and new file
//execute, expand, ft_(exit,export,unset), init, pipe, sytax 라인 수정




//서지네 컴파일러
//맥 클러스터
//gcc -L/Users/seojchoi/.brew/opt/readline/lib -lreadline -I/Users/seojchoi/.brew/opt/readline/include *.c libft.a -g -fsanitize=address
//맥 개인 맥북
//gcc -L/opt/homebrew/opt/readline/lib -l readline -I/opt/homebrew/opt/readline/include *.c libft.a -g -fsanitize=address

//태현이네 컴파일러
//맥 클러스터
//gcc -L/Users/taehkwon/.brew/opt/readline/lib -lreadline -I/Users/taehkwon/.brew/opt/readline/include *.c libft.a -g -fsanitize=address
//맥 개인 맥북
//gcc -L/opt/homebrew/opt/readline/lib -l readline -I/opt/homebrew/opt/readline/include *.c libft.a -g -fsanitize=address

