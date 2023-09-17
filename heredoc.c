/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:06:17 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/17 12:16:35 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc(char	*limiter, char	*tmp_file)
{
	char	*input;
	int		file_fd;

	signal(SIGINT, handler_sig_child);
	signal(SIGTERM, handler_sig_child);
	signal(SIGQUIT, SIG_IGN);
	file_fd = open(tmp_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (is_limiter(input, limiter))
		{
			free(input);
			break ;
		}
		ft_putendl_fd(input, file_fd);
		free(input);
	}
	close(file_fd);
}

void	fork_and_read_heredoc(t_data *cmd, int *status)
{
	t_data	*iter;
	t_redir	*r_iter;

	signal(SIGINT, SIG_IGN);
	if (!is_heredoc_process(cmd))
		return ;
	if (fork() == 0)
	{
		iter = cmd;
		while (iter)
		{
			r_iter = iter->redir;
			while (r_iter)
			{
				if (ft_strcmp(r_iter->redir, "<<") == 0)
					read_heredoc(r_iter->limiter, r_iter->file_name);
				r_iter = r_iter->next;
			}
			iter = iter->next;
		}
		exit(0);
	}
	if (waitpid(-1, status, 0) > 0)
		g_stat = WEXITSTATUS(*status);
}

int	here_doc(t_data *cmd)
{
	int		size;
	int		status;
	t_data	*iter;

	set_heredoc_tmp_file(cmd);
	fork_and_read_heredoc(cmd, &status);
	iter = cmd;
	size = 0;
	while (iter)
	{
		size++;
		iter = iter->next;
	}
	return (size);
}
