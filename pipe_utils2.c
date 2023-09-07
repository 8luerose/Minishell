/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 03:27:40 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/07 03:50:30 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//원본 코드
// void	do_cmd(t_data *cmd, t_envp *my_envp, char **path)
// {
// 	int		check;
// 	char	*access_path;

// 	if (cmd->cmd_line != NULL)
// 		check = is_builtin(cmd);
// 	else
// 		exit(0);
// 	if (check != NOT_BUILTIN)
// 	{
// 		cmd->o_fd = 1;
// 		run_builtin(check, cmd, my_envp->envp);
// 		exit(0);
// 	}
// 	else
// 	{
// 		access_path = check_is_access(cmd->cmd_line[0], path);
// 		if (!access_path)
// 		{
// 			if (!path)
// 			{
// 				ft_putstr_fd(cmd->cmd_line[0], 2);
// 				ft_putendl_fd(": No such file or directory", 2);
// 				g_stat = 126;
// 				exit(g_stat);
// 			}
// 			else
// 			{
// 				ft_putstr_fd(cmd->cmd_line[0], 2);
// 				ft_putendl_fd(": command not found", 2);
// 				g_stat = 127;
// 				exit(g_stat);
// 			}
// 		}
// 		else
// 		{
// 			set_ev(my_envp);
// 			if (execve(access_path, cmd->cmd_line, my_envp->ev) < 0)
// 				command_error(cmd->cmd_line[0], access_path);
// 		}
// 	}
// 	exit(0);
// }

void	do_cmd_error(t_data *cmd, char **path)
{
	ft_putstr_fd(cmd->cmd_line[0], 2);
	if (!path)
	{
		ft_putendl_fd(": No such file or directory", 2);
		g_stat = 126;
	}
	else
	{
		ft_putendl_fd(": command not found", 2);
		g_stat = 127;
	}
	exit(g_stat);
}

void	do_cmd_builtin(t_data *cmd, t_envp *my_envp)
{
	cmd->o_fd = 1;
	run_builtin(is_builtin(cmd), cmd, my_envp->envp);
	exit(0);
}

void	do_cmd_exec(t_data *cmd, t_envp *my_envp, char *access_path)
{
	set_ev(my_envp);
	if (execve(access_path, cmd->cmd_line, my_envp->ev) < 0)
		command_error(cmd->cmd_line[0], access_path);
}

void	do_cmd(t_data *cmd, t_envp *my_envp, char **path)
{
	char	*access_path;
	int		check;

	if (!cmd->cmd_line)
		exit(0);
	check = is_builtin(cmd);
	if (check != NOT_BUILTIN)
		do_cmd_builtin(cmd, my_envp);
	access_path = check_is_access(cmd->cmd_line[0], path);
	if (!access_path)
		do_cmd_error(cmd, path);
	else
		do_cmd_exec(cmd, my_envp, access_path);
	exit(0);
}
