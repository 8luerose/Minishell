/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:11:40 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/12 20:14:15 by taehkwon         ###   ########.fr       */
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
    (void)key;
    write(1, "\n💭 : ", 7);
	// exit(1);
}

void	handler_sigquit(int key)
{
    (void)key;  // 아무것도 하지 않음
}