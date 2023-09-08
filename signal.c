/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:11:40 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/09 04:53:26 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	handler_sigint(int key)
{
	if (key == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_stat = 1;
}

void	handler_sigterm(void)
{
	write(STDOUT_FILENO, "\033[1A", 4);
	write(STDOUT_FILENO, "\033[1C", 5);
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
