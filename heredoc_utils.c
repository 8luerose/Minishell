/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 03:42:56 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/17 12:16:17 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_heredoc_process(t_data	*cmd)
{
	t_data	*iter;
	t_redir	*r_iter;

	iter = cmd;
	while (iter)
	{
		r_iter = iter->redir;
		while (r_iter)
		{
			if (ft_strcmp(r_iter->redir, "<<") == 0)
				return (1);
			r_iter = r_iter->next;
		}
		iter = iter->next;
	}
	return (0);
}

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
				free(r_iter->file_name);
				r_iter->file_name = tmp;
				close(iter->i_fd);
			}
			r_iter = r_iter->next;
		}
		iter = iter->next;
	}
}
