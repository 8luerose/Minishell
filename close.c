/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:05:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/07 19:08:27 by taehkwon         ###   ########.fr       */
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

void	close_n_wait(t_pipe *fd, int size)
{
	int	i;
	int	status;

	close_prev(fd);
	close_cur(fd);
    i = 0;
	while (i < size)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				g_stat = WEXITSTATUS(status);
			else if (WTERMSIG(status) == 2)
				g_stat = 130;
			else if (WTERMSIG(status) == 3)
			{
				g_stat = 131;
				printf("QUIT: 3\n");
			}
		}
        i++;
	}
}
