/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:11:54 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/17 14:47:57 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_pipe(t_data *cmd, t_pipe *exec, t_envp *my_envp, char **path)
{
	if (set_io_fd(cmd) == 1)
		exit(1);
	dup2(cmd->i_fd, 0);
	if (cmd->o_fd != 1)
	{
		dup2(cmd->o_fd, 1);
		close(cmd->o_fd);
	}
	else if (exec->size > 1)
	{
		dup2(exec->cur_fd[1], 1);
		close(exec->cur_fd[1]);
	}
	if (cmd->i_fd != 0)
		close(cmd->i_fd);
	close(exec->cur_fd[0]);
	close_prev(exec);
	do_cmd(cmd, my_envp, path);
}

void	mid_pipe(t_data *cmd, t_pipe *fd, t_envp *my_envp, char **path)
{
	if (set_io_fd(cmd) == 1)
		exit(1);
	if (cmd->i_fd == 0)
	{
		dup2(fd->prev_fd[0], 0);
		close(fd->prev_fd[0]);
	}
	else
	{
		dup2(cmd->i_fd, 0);
		close(cmd->i_fd);
	}
	if (cmd->o_fd == 1)
	{
		dup2(fd->cur_fd[1], 1);
		close(fd->cur_fd[1]);
	}
	else
	{
		dup2(cmd->o_fd, 1);
		close(cmd->o_fd);
	}
	close(fd->prev_fd[1]);
	close(fd->cur_fd[0]);
	do_cmd(cmd, my_envp, path);
}

void	last_pipe(t_data *cmd, t_pipe *fd, t_envp *my_envp, char **path)
{
	if (set_io_fd(cmd) == 1)
		exit(1);
	if (cmd->i_fd == 0)
	{
		dup2(fd->prev_fd[0], 0);
		close(fd->prev_fd[0]);
	}
	else
	{
		dup2(cmd->i_fd, 0);
		close(cmd->i_fd);
	}
	dup2(cmd->o_fd, 1);
	if (cmd->o_fd != 1)
		close(cmd->o_fd);
	close(fd->prev_fd[1]);
	close_cur(fd);
	do_cmd(cmd, my_envp, path);
}
