/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 05:01:43 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/04 20:33:04 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_path(char **access_path, char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*tmp_path;

	i = 0;
	while (path && path[i])
	{
		tmp_path = ft_strjoin(path[i], "/");
		tmp = tmp_path;
		tmp_path = ft_strjoin(tmp, cmd);
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

// int	do_cmd(t_data	*cmd, t_envp *my_envp, char **path)
// {
// 	int		check;
// 	char	*access_path;

// 	access_path = NULL;
// 	if (cmd->cmd_line != NULL)
// 		check = is_builtin(cmd);
// 	else
// 		return (1);
// 	if (ft_strchr(cmd->cmd_line[0], '/'))
// 	{
// 		if (access(cmd->cmd_line[0], F_OK) == 0)
// 		{
// 			if (execve(cmd->cmd_line[0], cmd->cmd_line, my_envp->ev) < 0)
// 				system_error();
// 		}
// 		else
// 			file_error(cmd->cmd_line[0]);
// 	}
// 	else if (check != NOT_BUILTIN)
// 	{
// 		cmd->o_fd = 1;
// 		run_builtin(check, cmd, my_envp->envp);
// 		return (1);
// 	}
// 	else if (check_is_access(&access_path, path, cmd->cmd_line[0]))
// 	{
// 		if (execve(access_path, cmd->cmd_line, my_envp->ev) < 0)
// 			system_error();
// 	}
// 	else
// 		command_error(cmd->cmd_line[0]);
// 	return (0);
// }

char	*check_is_access(char	*cmd, char **path)
{
	char	*access_path;

	if (ft_strchr(cmd, '/')) // 절대 경로로 들어오는 경우
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
	}
	else if (make_path(&access_path, path, cmd))  // 상대 경로로 들어오는 경우
	{
		if (access(access_path, F_OK) == 0)
			return (access_path);	
	}
	return (0);
}

int	do_cmd(t_data	*cmd, t_envp *my_envp, char **path)
{
	int		check;
	char	*access_path;

	if (cmd->cmd_line != NULL)
		check = is_builtin(cmd);
	else
		return (1);
	if (check != NOT_BUILTIN)
	{
		cmd->o_fd = 1;
		run_builtin(check, cmd, my_envp->envp);
		return (1);
	}
	else
	{
		access_path = check_is_access(cmd->cmd_line[0], path);  // 경로가 붙어서 나옴.
		if (!access_path)
		{
			write(2, cmd->cmd_line[0], ft_strlen(cmd->cmd_line[0]));
			ft_putendl_fd(" : command not found", 2);
			exit(127);
		}
		else if (execve(access_path, cmd->cmd_line, my_envp->ev) < 0) // access는 성공했는데 execve 가 실패했을 경우
		{
			// 경로는 있지만 디렉토리
			// 실행권한이 없거나...
		}
	}
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
			if (iter->file_name)
				unlink(iter->file_name);
		}
		iter = iter->next;
	}
}

void	unlink_tmp_file_all(t_data	*cmd)
{
	t_data	*iter;

	iter = cmd;
	while (iter)
	{
		unlink_tmp_file(iter);
		iter = iter->next;
	}
}
