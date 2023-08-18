/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:06:17 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/19 02:10:07 by taehkwon         ###   ########.fr       */
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

int	is_limiter(char *str, char *limiter)
{
	int	i;

	i = 0;
	while (str[i] && limiter[i])
	{
		if (str[i] != limiter[i])
			return (0);
		i++;
	}
	if (!(str[i] == '\0' && limiter[i] == '\0'))
		return (0);
	return (1);
}

void	read_heredoc(char	*limiter, int file_fd)
{
	pid_t	pid;
	char	*input;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handler_sig_heredoc);
		signal(SIGTERM, handler_sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
		while (1)
		{
			input = readline("> ");
			if (is_limiter(input, limiter))
				break ;
			ft_putendl_fd(input, file_fd);
			free(input);
		}
	}
	free(limiter);
	waitpid(-1, 0, 0);
}

void	heredoc_open(t_data	*cmd)
{
	t_redir	*iter;
	char	*tmp_file;

	iter = cmd->redir;
	while (iter)
	{
		if (ft_strcmp(iter->redir, "<<") == 0)
		{
			tmp_file = set_file_name();
			cmd->i_fd = open(tmp_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			read_heredoc(iter->file_name, cmd->i_fd);
			iter->file_name = tmp_file;
			close(cmd->i_fd);
		}
		iter = iter->next;
	}
}
