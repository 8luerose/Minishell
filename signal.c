/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:11:40 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/18 17:04:20 by taehkwon         ###   ########.fr       */
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

void	set_terminal_print_on(void)		// 터미널에 ^C, ^\등의 시그널표식을 출력하도록 설정
{
	struct termios	term;
	tcgetattr(1, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(1, 0, &term);
}

void	handler_sigint(int key)
{
    // (void)key;
	// exit(1);
	if (key == SIGINT)					//지금까지 입력된 프롬프트를 유지한 채 개행한 후 텅 빈 프롬프트를 받는다
	{
		// write(1, "\n💭 : ", 7);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	if (key == SIGQUIT)
		(void)key;
}
