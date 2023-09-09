/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:01:21 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/10 06:54:41 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
