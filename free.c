/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 04:40:29 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/11 04:47:02 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipeline(t_data *data)
{
	t_data 	*tmp;

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
	int 	i;

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
		free(redir_tmp);
	}
}