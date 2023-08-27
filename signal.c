/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:11:40 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/27 20:27:57 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_terminal_print_off(void)	// 터미널에 ^C, ^\등의 시그널표식을 출력하지않도록 설정
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	handler_sigint(int key)
{
	if (key == SIGINT)					//지금까지 입력된 프롬프트를 유지한 채 개행한 후 텅 빈 프롬프트를 받는다
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	stat = 1;
}

void	handler_sigterm(void)
{
	// write (1, "exit\n", 5);
	// exit(0);
    // printf("\033[1A");
	// printf("\033[10C");
    // printf(" exit\n");
	write(STDOUT_FILENO, "\033[1A", 4);     // ANSI escape code를 사용하여 커서를 위로 1줄 움직이는 것 (\033['1'A)
    write(STDOUT_FILENO, "\033[5C", 5);   	// 커서를 n만큼 앞으로 전진시킨다. (\033['N'C) 에서 N
    write(STDOUT_FILENO, " exit\n", 6); 
    exit(0);
}

void	handler_sig_child(int key)
{
	if (key == SIGTERM)
		exit(0);
	if (key == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}
