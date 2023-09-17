/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 05:01:43 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/17 14:48:40 by seojchoi         ###   ########.fr       */
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
		tmp = ft_strdup(tmp_path);
		free(tmp_path);
		tmp_path = ft_strjoin(tmp, cmd);
		free(tmp);
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

char	*check_is_access(char	*cmd, char **path)
{
	char	*access_path;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	else if (make_path(&access_path, path, cmd))
	{
		if (access(access_path, F_OK) == 0)
			return (access_path);
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
