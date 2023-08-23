/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:11:54 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/24 02:50:13 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_access(char **access_path, char **path, char *cmd)
{
	int		i;
	char	*tmp_path;

	i = 0;
	while (path[i])
	{
		tmp_path = ft_strjoin(path[i], "/");
		tmp_path = ft_strjoin(tmp_path, cmd);
		if (!access(tmp_path, F_OK))
		{
			*access_path = ft_strdup(tmp_path);
			return (1);
		}
		free(tmp_path);
		i++;
	}
	return (0);
}

int	do_cmd(t_data	*cmd, t_envp *my_envp, char **path)
{
	int		check;
	char	*access_path;

	access_path = NULL;
	check = is_builtin(cmd);
	if (ft_strchr(cmd->cmd_line[0], '/'))
	{
		if (access(cmd->cmd_line[0], F_OK) == 0)
			execve(cmd->cmd_line[0], cmd->cmd_line, my_envp->ev);
		else
			file_error(cmd->cmd_line[0]);
	}
	else if (check != NOT_BUILTIN)
	{
		cmd->o_fd = 1;
		run_builtin(check, cmd, my_envp->envp);
		return (1);
	}
	else if (check_is_access(&access_path, path, cmd->cmd_line[0]))
		execve(access_path, cmd->cmd_line, my_envp->ev);
	else
		command_error(cmd->cmd_line[0]);
	return (0);
}

void	unlink_tmp_file(t_data	*cmd)
{
	t_redir	*iter;

	iter = cmd->redir;
	while (iter)
	{
		if (ft_strcmp(iter->redir, "<<") == 0)
		{
			unlink(iter->file_name);
		}
		iter = iter->next;
	}
}

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
