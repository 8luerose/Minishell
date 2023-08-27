/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:06:17 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/28 01:29:10 by taehkwon         ###   ########.fr       */
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
	int		status;

	signal(SIGINT, SIG_IGN);									//fork 전 추가	
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handler_sig_child);
		signal(SIGTERM, handler_sig_child);
		signal(SIGQUIT, SIG_IGN);
		// signal(SIGQUIT, handler_sig_child);
		// signal(SIGQUIT, SIG_DFL);
		while (1)
		{
			input = readline("> ");
			if (!input)
				break ;
			if (is_limiter(input, limiter))
				break ;
			ft_putendl_fd(input, file_fd);
			free(input);
		}
		exit(0);
	}
	free(limiter);
	if (waitpid(-1, &status, 0) > 0)
	{
		stat = WEXITSTATUS(status);					//limiter 일때 Ctrl + c 누르면 stat = 1
		printf("heredoc stat: %d\n", stat);

		// // if (WIFEXITED(status))				// 자식 프로세스가 정상적으로 종료되었을 경우
		// // 	stat = WEXITSTATUS(status);		// 자식 프로세스가 반환한 값을 stat에 저장
		// if (WTERMSIG(status) == 2)		// SIGINT(Ctrl+C)=2
		// 	stat = 1;
	}
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
