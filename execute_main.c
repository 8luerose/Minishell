/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:01:21 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/07 19:15:58 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exec_backup(&exec, i);
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
