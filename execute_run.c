/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:15:15 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/17 12:20:30 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_ev(t_envp	*my_envp)
{
	int		size;
	t_node	*iter;

	size = 0;
	iter = my_envp->envp->head;
	while (iter)
	{
		size++;
		iter = iter->next;
	}
	my_envp->ev = (char **)malloc(sizeof(char *) * (size + 1));
	size = 0;
	iter = my_envp->envp->head;
	while (iter)
	{
		my_envp->ev[size] = ft_strdup(iter->content);
		size++;
		iter = iter->next;
	}
	my_envp->ev[size] = 0;
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
	free(key);
	return (path);
}

int	set_io_fd_open(t_redir *iter)
{
	int		fd;
	char	*file_name;

	fd = -1;
	file_name = iter->file_name;
	if (check_ambiguous(file_name, iter))
		return (fd);
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

void	exec_cmd(int i, t_data *iter, t_pipe *exec, t_envp *my_envp)
{
	char	**path_cp;

	path_cp = my_envp->path;
	signal(SIGINT, handler_sig_child);
	signal(SIGTERM, handler_sig_child);
	signal(SIGQUIT, SIG_DFL);
	if (i == 0)
		first_pipe(iter, exec, my_envp, path_cp);
	else if (!iter->next)
		last_pipe(iter, exec, my_envp, path_cp);
	else
		mid_pipe(iter, exec, my_envp, path_cp);
}
