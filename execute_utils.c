/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:15:15 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/17 12:20:24 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_backup(t_pipe *fd, int i)
{
	if (i != 0)
	{
		fd->prev_fd[0] = fd->cur_fd[0];
		fd->prev_fd[1] = fd->cur_fd[1];
	}
}

int	check_ambiguous(char *file_name, t_redir *iter)
{
	int		size;
	char	**tmp;

	if (ft_strcmp(iter->redir, "<<") != 0)
	{
		tmp = ft_split(file_name, ' ');
		size = 0;
		while (tmp[size])
		{
			size++;
		}
		free_all(tmp);
		if (size > 1 || ft_strlen(file_name) == 0)
		{
			g_stat = 1;
			ft_putendl_fd("ambiguous redirect", 2);
			return (1);
		}
	}
	return (0);
}
