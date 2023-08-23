/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 05:01:43 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/24 05:02:03 by taehkwon         ###   ########.fr       */
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