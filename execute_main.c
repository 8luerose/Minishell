/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:01:21 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/10 06:50:48 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 원본 코드
// void	run(t_data *cmd, int size, t_envp *my_envp)
// {
// 	int		i;
// 	char	**path;
// 	pid_t	pid;
// 	t_data	*iter;
// 	t_pipe	exec;

// 	path = get_envp_path(get_ev(my_envp->envp));
// 	exec.size = size;
// 	iter = cmd;
// 	if (pipe(exec.prev_fd) < 0 || (i = 0) < 0)
// 		exit(1);
// 	while (iter)
// 	{
// 		if (i > 0)
// 			close_prev(&exec);
// 		exec_backup(&exec, i);
// 		signal(SIGINT, SIG_IGN);
// 		if (pipe(exec.cur_fd) < 0 || (pid = fork()) < 0)
// 			exit(1);
// 		if (pid == 0)
// 			exec_cmd(i, iter, &exec, my_envp, path);
// 		i++;
// 		iter = iter->next;
// 	}
// 	close_n_wait(&exec, i);
// }

//2차 수정
// void	run(t_data *cmd, int size, t_envp *my_envp)
// {
// 	int		i;
// 	char	**path;
// 	pid_t	pid;
// 	t_data	*iter;
// 	t_pipe	exec;

// 	path = get_envp_path(get_ev(my_envp->envp));
// 	exec.size = size;
// 	iter = cmd;
// 	if (pipe(exec.prev_fd) < 0)
// 		exit(1);
// 	i = 0;
// 	while (iter)
// 	{
// 		if (i > 0)
// 			close_prev(&exec);
// 		exec_backup(&exec, i);
// 		signal(SIGINT, SIG_IGN);
// 		if (pipe(exec.cur_fd) < 0)
// 			exit(1);
// 		pid = fork();
// 		if (pid == 0)
// 			exec_cmd(i, iter, &exec, my_envp, path);
// 		i++;
// 		iter = iter->next;
// 	}
// 	close_n_wait(&exec, i);
// }

void	set_env_pipe(t_envp *my_envp, t_pipe *exec, char ***path, int size)
{
	*path = get_envp_path(get_ev(my_envp->envp));
	my_envp->path = *path;
	exec->size = size;
	if (pipe(exec->prev_fd) < 0)
		exit(1);
}

void	exec_close_backup(int i, t_pipe *exec)
{
	if (i > 0)
		close_prev(exec);
	exec_backup(exec, i);
	signal(SIGINT, SIG_IGN);
	if (pipe(exec->cur_fd) < 0)
		exit(1);
}

void	run(t_data *cmd, int size, t_envp *my_envp)
{
	int		i;
	char	**path;
	pid_t	pid;
	t_data	*iter;
	t_pipe	exec;

	set_env_pipe(my_envp, &exec, &path, size);
	i = 0;
	iter = cmd;
	while (iter)
	{
		exec_close_backup(i, &exec);
		pid = fork();
		if (pid == 0)
			exec_cmd(i, iter, &exec, my_envp);
		i++;
		iter = iter->next;
	}
	close_n_wait(&exec, i);
}

///////////////////////////////////////////////////////////////////////////////////////

//예비용 + 메인문 다름
// void setup_env_and_pipe(t_envp *my_envp, t_pipe *exec, char ***path, int size)
// {
//     *path = get_envp_path(get_ev(my_envp->envp));
//     exec->size = size;
//     if (pipe(exec->prev_fd) < 0)
//         exit(1);
// }

// void iterate_cmds(t_data *cmd, t_pipe *exec, t_envp *my_envp, char **path)
// {
//     int i = 0;
//     pid_t pid;
//     t_data *iter = cmd;
    
//     while (iter)
//     {
//         if (i > 0)
//             close_prev(exec);
//         exec_backup(exec, i);
//         signal(SIGINT, SIG_IGN);
//         if (pipe(exec->cur_fd) < 0)
//             exit(1);
//         pid = fork();
//         if (pid == 0)
//             exec_cmd(i, iter, exec, my_envp, path);
//         i++;
//         iter = iter->next;
//     }
//     close_n_wait(exec, i);
// }

// void run(t_data *cmd, int size, t_envp *my_envp)
// {
//     char **path;
//     t_pipe exec;

//     setup_env_and_pipe(my_envp, &exec, &path, size);
//     iterate_cmds(cmd, &exec, my_envp, path);
// }

int	builtins_check(t_data *cmd, t_envp *my_envp)
{
	int	check;

	if (set_io_fd(cmd) == 1)
		return (1);
	check = is_builtin(cmd);
	if (check == EXIT)
	{
		ft_putendl_fd("exit", 1);
		ft_exit(cmd->cmd_line);
	}
	else if (check != NOT_BUILTIN)
	{
		run_builtin(check, cmd, my_envp->envp);
		return (0);
	}
	return (-1);
}

int	execute(t_data *cmd, t_envp *my_envp)
{
	int	size;
	int	error_value;
	int	builtin_value;

	g_stat = 0;
	size = here_doc(cmd);
	error_value = exec_error_check(cmd);
	if (error_value != -1)
		return (error_value);
	if (size == 1 && cmd->cmd_line)
	{
		builtin_value = builtins_check(cmd, my_envp);
		if (builtin_value != -1)
			return (builtin_value);
	}
	run(cmd, size, my_envp);
	return (0);
}
