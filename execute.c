/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:01:21 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/23 01:12:10 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_prev(t_pipe *fd)
{
	close(fd->prev_fd[0]);
	close(fd->prev_fd[1]);
}

void	close_cur(t_pipe *fd)
{
	close(fd->cur_fd[0]);
	close(fd->cur_fd[1]);
}

//서지님 원본 코드
// void	close_n_wait(t_pipe *fd, int size)
// {
// 	int	i;

// 	close_prev(fd);
// 	close_cur(fd);
// 	i = 0;
// 	while (i < size)
// 	{
// 		waitpid(-1, 0, 0);  // 프로세스 번호가 반환됨 (stat에)
// 		i++;
// 	}
// }

void close_n_wait(t_pipe *fd, int size)			// 자식 프로세스가 종료될 때까지 기다리는 함수, size = 자식 프로세스 개수
{
    int i;
    int status;

    close_prev(fd);
    close_cur(fd);
    i = 0;
    while (i < size)
    {
        if (waitpid(-1, &status, 0) > 0)		// waitpid 함수는 자식 프로세스가 종료될 때까지 부모 프로세스를 대기 상태로 만듦
        {
            if (WIFEXITED(status))				// 자식 프로세스가 정상적으로 종료되었을 경우
                stat = WEXITSTATUS(status);		// 자식 프로세스가 반환한 값을 stat에 저장
            else if (WTERMSIG(status) == 2)		// SIGINT(Ctrl+C)=2
                stat = 130;						// 일반적으로 프로그램이 시그널로 종료될 때, 종료 상태는 시그널 번호에 128을 더한 값으로 설정
            else if (WTERMSIG(status) == 3)		//SIGQUIT(Ctrl+\)=3
            {
                stat = 131;						//128 + 3(SIGQUT) = 131
                printf("QUIT: 3\n");			// QUIT: 3은 SIGQUIT 시그널로 프로세스가 종료되었을 때 출력되는 메시지. 3은 SIGQUIT 시그널의 번호
            }
        }
        i++;
    }
}

int	set_io_fd(t_data *cmd)
{
	char	*file_name;
	t_redir	*iter;

	cmd->i_fd = 0;
	cmd->o_fd = 1;
	iter = cmd->redir;
	while (iter)
	{
		file_name = iter->file_name;
		if (ft_strcmp(iter->redir, "<") == 0)
		{
			cmd->i_fd = open(file_name, O_RDONLY);
			if (cmd->i_fd < 0)
				return (file_error(file_name));
			close(cmd->i_fd);
		}
		else if (ft_strcmp(iter->redir, "<<") == 0)
		{
			cmd->i_fd = open(file_name, O_RDONLY);
			if (cmd->i_fd < 0)
				return (file_error(file_name));
			close(cmd->i_fd);
		}
		else if (ft_strcmp(iter->redir, ">") == 0)
		{
			cmd->o_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->o_fd < 0)
				return (file_error(file_name));
			close(cmd->o_fd);
		}
		else if (ft_strcmp(iter->redir, ">>") == 0)
		{
			cmd->o_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd->o_fd < 0)
				return (file_error(file_name));
			close(cmd->o_fd);
		}
		iter = iter->next;
	}
	return (0);
}

void	backup(t_pipe *fd, int i)
{
	if (i != 0)
	{
		fd->prev_fd[0] = fd->cur_fd[0];
		fd->prev_fd[1] = fd->cur_fd[1];
	}
}

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

void	run(t_data *cmd, int size, t_envp *my_envp)
{
	int		i;
	char	**path;
	pid_t	pid;
	t_data	*iter;
	t_pipe	exec;

	my_envp->ev = get_ev(my_envp->envp);
	path = get_envp_path(my_envp->ev);
	exec.size = size;
	iter = cmd;
	if (pipe(exec.prev_fd) < 0)
		exit(1);
	i = 0;
	while (iter)
	{
		if (i > 0)
			close_prev(&exec);
		backup(&exec, i);
		if (pipe(exec.cur_fd) < 0)
			exit(1);
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			signal(SIGINT, handler_sig_child);
			signal(SIGTERM, handler_sig_child);
			signal(SIGQUIT, SIG_IGN);
			if (i == 0)
				first_pipe(iter, &exec, my_envp, path);
			else if (iter->next == NULL)
				last_pipe(iter, &exec, my_envp, path);
			else
				mid_pipe(iter, &exec, my_envp, path);
		}
		i++;
		iter = iter->next;
	}
	close_n_wait(&exec, i);
}

int	execute(t_data	*cmd, t_envp	*my_envp)
{
	int		check;
	int		size;
	t_data	*iter;

	size = 0;
	iter = cmd;
	while (iter)
	{
		size++;
		heredoc_open(iter);
		iter = iter->next;
	}
	if (size == 1 && cmd->cmd_line != NULL)
	{
		if (set_io_fd(cmd) == 1)
			return (1);
		check = is_builtin(cmd);
		if (check != NOT_BUILTIN)
		{
			run_builtin(check, cmd, my_envp->envp);
			return (0);
		}
	}
	run(cmd, size, my_envp);
	return (0);
}
