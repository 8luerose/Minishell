/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:21:43 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/12 12:54:13 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipeline(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data;
		data = data->next;
		free_cmd_line(tmp->cmd_line);
		free_redirs(tmp->redir);
		free(tmp);
	}
}

void	free_cmd_line(char **cmd_line)
{
	int	i;

	i = 0;
	if (cmd_line)
	{
		while (cmd_line[i])
		{
			free(cmd_line[i]);
			i++;
		}
		free(cmd_line);
	}
}

void	free_redirs(t_redir *redir)
{
	t_redir	*redir_tmp;

	while (redir)
	{
		redir_tmp = redir;
		redir = redir->next;
		free(redir_tmp->redir);
		free(redir_tmp->file_name);
		free(redir_tmp->limiter);
		free(redir_tmp);
	}
}

void	free_list(t_data *pipe_parsing)
{
	int		i;
	t_data	*cmd_iter;
	t_data	*cmd_next;
	t_redir	*redir_iter;

	cmd_iter = pipe_parsing;
	while (cmd_iter)
	{
		if (cmd_iter->cmd_line)
		{
			i = 0;
			while (cmd_iter->cmd_line[i])
			{
				free(cmd_iter->cmd_line[i]);
				i++;
			}
			free(cmd_iter->cmd_line);
		}
		redir_iter = cmd_iter->redir;
		free_redirs(redir_iter);
		cmd_next = cmd_iter->next;
		free(cmd_iter);
		cmd_iter = cmd_next;
	}
}

void	free_token(t_list	*list)
{
	t_node	*next;
	t_node	*iter;

	iter = list->head;
	while (iter)
	{
		free(iter->content);
		next = iter->next;
		free(iter);
		iter = next;
	}
	free(list);
}
