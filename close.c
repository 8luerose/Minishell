/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:05:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/06 17:11:27 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_prev(t_pipe *fd)
{
	close(fd->prev_fd[0]);
	close(fd->prev_fd[1]);
}

void	close_cur(t_pipe *fd)
{
	close(fd->cur_fd[0]);
	close(fd->cur_fd[1]);
}

void close_n_wait(t_pipe *fd, int size)			// 자식 프로세스가 종료될 때까지 기다리는 함수, size = 자식 프로세스 개수
{
    int i;
    int status;

    close_prev(fd);
    close_cur(fd);
    i = 0;
    while (i < size)
    {
        if (waitpid(-1, &status, 0) > 0)		// waitpid 함수는 자식 프로세스가 종료될 때까지 부모 프로세스를 대기 상태로 만듦
        {
            if (WIFEXITED(status))				// 자식 프로세스가 정상적으로 종료되었을 경우
                g_stat = WEXITSTATUS(status);		// 자식 프로세스가 반환한 값을 stat에 저장
            else if (WTERMSIG(status) == 2)		// SIGINT(Ctrl+C)=2
                g_stat = 130;						// 일반적으로 프로그램이 시그널로 종료될 때, 종료 상태는 시그널 번호에 128을 더한 값으로 설정
            else if (WTERMSIG(status) == 3)		//SIGQUIT(Ctrl+\)=3
            {
                g_stat = 131;						//128 + 3(SIGQUT) = 131
                printf("QUIT: 3\n");			// QUIT: 3은 SIGQUIT 시그널로 프로세스가 종료되었을 때 출력되는 메시지. 3은 SIGQUIT 시그널의 번호
            }
        }
        i++;
    }
}
