// void	minishell(char *input)
// {
// 	t_list	*list;
// 	t_data	*pipe_parsing;
// 	t_node 	*test;

// 	list = (t_list *)malloc(sizeof(t_list));
// 	list->head = NULL;
// 	list->tail = NULL;

// 	if (strcmp(input, "exit") == 0) // "exit" 명령 처리
//     {
//         free(list);
//         free(input);
//         exit(0);
//     }

// 	get_token(input, list);
// 	get_type(list);
// 	check_syntax_error(list);  // syntax 에러
// 	// expand(my_envp, list);
	
// 	pipe_parsing = NULL;
// 	get_list(list, &pipe_parsing);		//1차 토큰화 -> 파이프 단위로 나눔

// 	print_type(list);					//타입만 확인
// 	print_result_test(pipe_parsing);	//2차 파싱 잘 구분되었는지 테스트 출력
// 	print_result(pipe_parsing);			//2차 파싱 결과물 출력
// }

// void	handler_sigint(int key)
// {
//     (void)key;
//     write(1, "\n💭 : ", 7);
// }

// void	handler_sigquit(int key)
// {
//     (void)key;  // 아무것도 하지 않음
// }

// int	main(int ac, char **av, char **ev)
// {
//     char	*input;
//     t_list	*my_envp;

//     signal(SIGINT, handler_sigint);   // Ctrl + C
//     signal(SIGQUIT, handler_sigquit); // Ctrl + \

//     ac = 0;
//     av = 0;
//     my_envp = (t_list *)malloc(sizeof(t_list));
//     my_envp->head = NULL;
//     my_envp->tail = NULL;
//     copy_envp(ev, my_envp);

//     while (1)
//     {
//         input = readline("💭 : ");

//         if (!input) // ctrl + d (EOF) 입력하면 NULL들어온다
//         {
//             write(1, "\n", 1);
//             exit(0);  // 정상적 종료
//         }

//         if (*input)  // 입력(문자열)이 있으면 명령 처리
//         {
//             minishell(input);
//             add_history(input);
//         }
		
//         free(input);
//     }
//     return 0;
// }