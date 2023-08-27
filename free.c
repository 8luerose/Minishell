/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:21:43 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/27 13:47:35 by seojchoi         ###   ########.fr       */
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
		free(redir_tmp);
	}
}

void	cmd_exit(char *input, t_list *list)
{
	if (strcmp(input, "exit") == 0)		// "exit" 명령 처리
    {
        free(list);
        free(input);
		printf("exit\n");
        exit(0);
    }
}