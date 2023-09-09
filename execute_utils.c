/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:15:15 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/09 17:13:32 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_error_check(t_data *cmd)
{
	if (!cmd)
		return (0);
	if (g_stat != 0)
	{
		unlink_tmp_file_all(cmd);
		return (1);
	}
	return (-1);
}

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
