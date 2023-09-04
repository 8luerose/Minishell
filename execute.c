/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:01:21 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/04 20:39:50 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//원본 코드
// int	set_io_fd(t_data *cmd)
// {
// 	char	*file_name;
// 	t_redir	*iter;

// 	cmd->i_fd = 0;
// 	cmd->o_fd = 1;
// 	iter = cmd->redir;
// 	while (iter)
// 	{
// 		file_name = iter->file_name;
// 		if (ft_strcmp(iter->redir, "<") == 0)
// 		{
// 			cmd->i_fd = open(file_name, O_RDONLY);
// 			if (cmd->i_fd < 0)
// 				return (file_error(file_name));
// 			close(cmd->i_fd);
// 		}
// 		else if (ft_strcmp(iter->redir, "<<") == 0)
// 		{
// 			cmd->i_fd = open(file_name, O_RDONLY);
// 			if (cmd->i_fd < 0)
// 				return (file_error(file_name));
// 			close(cmd->i_fd);
// 		}
// 		else if (ft_strcmp(iter->redir, ">") == 0)
// 		{
// 			cmd->o_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (cmd->o_fd < 0)
// 				return (file_error(file_name));
// 			close(cmd->o_fd);
// 		}
// 		else if (ft_strcmp(iter->redir, ">>") == 0)
// 		{
// 			cmd->o_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (cmd->o_fd < 0)
// 				return (file_error(file_name));
// 			close(cmd->o_fd);
// 		}
// 		iter = iter->next;
// 	}
// 	return (0);
// }

int	have_space (char	*file_name)
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

int	set_io_fd_open(t_redir *iter)
{
	int		fd;
	char	*file_name;

	fd = -1;
	file_name = iter->file_name;
	if ((ft_strcmp(iter->redir, "<") == 0) && ( ft_strlen(file_name) == 0 || have_space(file_name)))
	{
		stat = 1;
		printf("bash : ambiguous redirect\n");
		// return (fd);
		exit(stat);
	}
	if (ft_strcmp(iter->redir, "<") == 0 || ft_strcmp(iter->redir, "<<") == 0)
		fd = open(file_name, O_RDONLY);
	else if (ft_strcmp(iter->redir, ">") == 0)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(iter->redir, ">>") == 0)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		file_error(file_name);
		return (fd);
	}
	// close(fd);
	return (fd);
}

int	set_io_fd(t_data *cmd)
{
	t_redir	*iter;

	cmd->i_fd = 0;
	cmd->o_fd = 1;
	iter = cmd->redir;
	while (iter)
	{
		if (ft_strcmp(iter->redir, "<") == 0
			|| ft_strcmp(iter->redir, "<<") == 0)
			cmd->i_fd = set_io_fd_open(iter);
		else if (ft_strcmp(iter->redir, ">") == 0
			|| ft_strcmp(iter->redir, ">>") == 0)
			cmd->o_fd = set_io_fd_open(iter);
		iter = iter->next;
		if (cmd->o_fd == -1 || cmd->i_fd == -1)
			return (1);
	}
	return (0);
}

// 원본 코드
// void	run(t_data *cmd, int size, t_envp *my_envp)
// {
// 	int		i;
// 	char	**path;
// 	pid_t	pid;
// 	t_data	*iter;
// 	t_pipe	exec;

// 	my_envp->ev = get_ev(my_envp->envp);
// 	path = get_envp_path(my_envp->ev);
// 	exec.size = size;
// 	iter = cmd;
// 	if (pipe(exec.prev_fd) < 0)
// 		exit(1);
// 	i = 0;
// 	while (iter)
// 	{
// 		if (i > 0)
// 			close_prev(&exec);
// 		exec_backup(&exec, i);						//backup -> exec_backup 이름 변경
// 		if (pipe(exec.cur_fd) < 0)
// 			exit(1);
// 		signal(SIGINT, SIG_IGN);
// 		pid = fork();
// 		if (pid < 0)
// 			exit(1);
// 		if (pid == 0)
// 		{
// 			signal(SIGINT, handler_sig_child);
// 			signal(SIGTERM, handler_sig_child);
// 			signal(SIGQUIT, SIG_IGN);
// 			if (i == 0)
// 				first_pipe(iter, &exec, my_envp, path);
// 			else if (iter->next == NULL)
// 				last_pipe(iter, &exec, my_envp, path);
// 			else
// 				mid_pipe(iter, &exec, my_envp, path);
// 		}
// 		i++;
// 		iter = iter->next;
// 	}
// 	close_n_wait(&exec, i);
// }

void	exec_cmd(int i, t_data *iter, t_pipe *exec, t_envp *my_envp, char **path)
{
	signal(SIGINT, handler_sig_child);
	signal(SIGTERM, handler_sig_child);
	// signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, SIG_DFL);
	if (i == 0)
		first_pipe(iter, exec, my_envp, path);
	else if (!iter->next)
		last_pipe(iter, exec, my_envp, path);
	else
		mid_pipe(iter, exec, my_envp, path);
}

// 1차 수정 코드
// void	run(t_data *cmd, int size, t_envp *my_envp)
// {
// 	int		i;
// 	char	**path;
// 	pid_t	pid;
// 	t_data	*iter;
// 	t_pipe	exec;

// 	my_envp->ev = get_ev(my_envp->envp);
// 	path = get_envp_path(my_envp->ev);
// 	exec.size = size;
// 	iter = cmd;
// 	if (pipe(exec.prev_fd) < 0)
// 		exit(1);
// 	i = 0;
// 	while (iter)
// 	{
// 		if (i > 0)
// 			close_prev(&exec);
// 		exec_backup(&exec, i);						//backup -> exec_backup 이름 변경
// 		if (pipe(exec.cur_fd) < 0)
// 			exit(1);
// 		signal(SIGINT, SIG_IGN);
// 		pid = fork();
// 		if (pid < 0)
// 			exit(1);
// 		if (pid == 0)
// 			exec_cmd(i, iter, &exec, my_envp, path);
// 		i++;
// 		iter = iter->next;
// 	}
// 	close_n_wait(&exec, i);
// }

void	run(t_data *cmd, int size, t_envp *my_envp)
{
	int		i;
	char	**path;
	pid_t	pid;
	t_data	*iter;
	t_pipe	exec;

	path = get_envp_path(get_ev(my_envp->envp));
	exec.size = size;
	iter = cmd;
	if (pipe(exec.prev_fd) < 0 || (i = 0) < 0)
		exit(1);
	while (iter)
	{
		if (i > 0)
			close_prev(&exec);
		exec_backup(&exec, i);								//backup -> exec_backup 이름 변경
		signal(SIGINT, SIG_IGN);
		if (pipe(exec.cur_fd) < 0 || (pid = fork()) < 0)
			exit(1);
		if (pid == 0)
			exec_cmd(i, iter, &exec, my_envp, path);
		i++;
		iter = iter->next;
	}
	close_n_wait(&exec, i);
}

int	execute(t_data	*cmd, t_envp	*my_envp)
{
	int		check;
	int		size;
	// t_data	*iter;

	stat = 0;
	// iter = cmd;
	// // 히어독 임시파일 이름 먼저 지정
	// while (iter)
	// {
	// 	size++;
	// 	heredoc_open(iter);
	// 	iter = iter->next;
	// }
	// // 파일 오픈해서 내용 저장
	size = here_doc(cmd);
	if (stat != 0)
	{
		unlink_tmp_file_all(cmd);
		return (1);
	}
	if (size == 1 && cmd->cmd_line != NULL)
	{
		if (set_io_fd(cmd) == 1)
			return (1);
		check = is_builtin(cmd);
		if (check != NOT_BUILTIN)
		{
			if (check == EXIT)
			{
				ft_putendl_fd("exit", 1);
				ft_exit(cmd->cmd_line);
			}
			else
				run_builtin(check, cmd, my_envp->envp);
			return (0);
		}
	}
	run(cmd, size, my_envp);
	return (0);
}
