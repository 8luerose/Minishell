/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_run_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:15:15 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/24 02:18:53 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_ev(t_list *my_envp)
{
	int		size;
	char	**ev;
	t_node	*iter;

	size = 0;
	iter = my_envp->head;
	while (iter)
	{
		size++;
		iter = iter->next;
	}
	ev = (char **)malloc(sizeof(char *) * (size + 1));
	size = 0;
	iter = my_envp->head;
	while (iter)
	{
		ev[size] = ft_strdup(iter->content);
		size++;
		iter = iter->next;
	}
	ev[size] = 0;
	return (ev);
}

char	**get_envp_path(char **ev)
{
	int		i;
	char	*key;
	char	**path;
	char	*envp_path;

	i = 0;
	key = ft_strdup("PATH=");
	path = NULL;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], key, ft_strlen(key)) == 0)
		{
			envp_path = ft_strtrim(ev[i], "PATH=");
			path = ft_split(envp_path, ':');
			free(envp_path);
			break ;
		}
		i++;
	}
	return (path);
}

void	exec_backup(t_pipe *fd, int i)
{
	if (i != 0)
	{
		fd->prev_fd[0] = fd->cur_fd[0];
		fd->prev_fd[1] = fd->cur_fd[1];
	}
}