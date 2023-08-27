/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:11:54 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/24 13:52:54 by seojchoi         ###   ########.fr       */
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
	unlink_tmp_file(cmd);
	if (do_cmd(cmd, my_envp, path))
		exit(0);
}

// 원본 코드
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
	if (do_cmd(cmd, my_envp, path))
		exit(0);
}

// void	mid_pipe_dup2(int cmd_fd, int fd, int *prev_fd, int *cur_fd)
// {
//     if (cmd_fd == fd) 
//     {
//         if (fd == 0) 
//         {
//             dup2(prev_fd[0], 0);
//             close(prev_fd[0]);
//         } 
//         else 
//         {
//             dup2(cur_fd[1], 1);
//             close(cur_fd[1]);
//         }
//     } 
//     else 
//     {
//         dup2(cmd_fd, fd);
//         close(cmd_fd);
//     }
// }

// void	mid_pipe(t_data *cmd, t_pipe *fd, t_envp *my_envp, char **path)
// {
//     mid_pipe_dup2(cmd->i_fd, 0, fd->prev_fd, fd->cur_fd);
//     mid_pipe_dup2(cmd->o_fd, 1, fd->prev_fd, fd->cur_fd);
//     close(fd->prev_fd[1]);
//     close(fd->cur_fd[0]);
//     if (do_cmd(cmd, my_envp, path))
//         exit(0);
// }

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
	if (do_cmd(cmd, my_envp, path))
		exit(0);
}
