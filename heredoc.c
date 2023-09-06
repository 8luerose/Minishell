/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:06:17 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/06 17:19:09 by taehkwon         ###   ########.fr       */
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
	if (!limiter)
		return (1);
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

void	read_heredoc(char	*limiter, char	*tmp_file)
{
	char	*input;
	int		file_fd;

	// signal(SIGINT, SIG_IGN);									//fork 전 추가	
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

// void	heredoc_open(t_data	*cmd)
// {
// 	int		status;
// 	pid_t	pid;
// 	t_redir	*iter;
// 	char	*tmp_file;

// 	signal(SIGINT, SIG_IGN);
// 	iter = cmd->redir;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		while (iter)
// 		{
// 			if (ft_strcmp(iter->redir, "<<") == 0)
// 			{
// 				tmp_file = set_file_name();
// 				cmd->i_fd = open(tmp_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 				read_heredoc(iter->file_name, cmd->i_fd);
// 				// printf("tmp: %s\n", tmp_file);
// 				iter->file_name = tmp_file;
// 				// printf("tmp: %s\n", iter->file_name);
// 				close(cmd->i_fd);
// 			}
// 			iter = iter->next;
// 		}
// 		exit(0);
// 	}
// 	if (waitpid(-1, &status, 0) > 0)
// 		stat = WEXITSTATUS(status);
// }

int	here_doc(t_data	*cmd)
{
	int		size;
	int		status;
	t_data	*iter;
	t_redir	*r_iter;
	pid_t	pid;
	char	*tmp_file;

	// 히어독 임시파일 이름 먼저 지정
	iter = cmd;
	size = 0;
	while (iter)
	{
		size++;
		r_iter = iter->redir;
		while (r_iter)
		{
			if (ft_strcmp(r_iter->redir, "<<") == 0)
			{
				tmp_file = set_file_name();
				iter->i_fd = open(tmp_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				r_iter->limiter = ft_strdup(r_iter->file_name);  // 히어독 뒤의 파이 이름은 리미터라서 갱신시켜 줌.
				r_iter->file_name = tmp_file;
				close(iter->i_fd);
			}
			r_iter = r_iter->next;
		}
		iter = iter->next;
	}
	// fork하는 부분
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
	if (waitpid(-1, &status, 0) > 0)
		g_stat = WEXITSTATUS(status);
	return (size);
}
