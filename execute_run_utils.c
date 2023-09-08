/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_run_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:15:15 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/09 04:43:48 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_backup(t_pipe *fd, int i)
{
	if (i != 0)
	{
		fd->prev_fd[0] = fd->cur_fd[0];
		fd->prev_fd[1] = fd->cur_fd[1];
	}
}

int	have_space(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
	{
		if (file_name[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
