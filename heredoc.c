/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:06:17 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/09 06:09:30 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_file_name(void)
{
	int		i;
	char	*num;
	char	*tmp;
	char	*file_name;

	i = 0;
	tmp = "tmp";
	while (1)
	{
		num = ft_itoa(i);
		file_name = ft_strjoin(tmp, num);
		free(num);
		if (access(file_name, F_OK) != 0)
			break ;
		free(file_name);
		i++;
	}
	return (file_name);
}

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

void	set_heredoc_tmp_file(t_data *cmd)
{
	t_data	*iter;
	t_redir	*r_iter;
	char	*tmp;

	iter = cmd;
	while (iter)
	{
		r_iter = iter->redir;
		while (r_iter)
		{
			if (ft_strcmp(r_iter->redir, "<<") == 0)
			{
				tmp = set_file_name();
				iter->i_fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
				r_iter->limiter = ft_strdup(r_iter->file_name);
				r_iter->file_name = tmp;
				close(iter->i_fd);
			}
			r_iter = r_iter->next;
		}
		iter = iter->next;
	}
}

void	fork_and_read_heredoc(t_data *cmd, int *status)
{
	pid_t	pid;
	t_data	*iter;
	t_redir	*r_iter;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
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
