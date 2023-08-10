/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:43:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/11 03:41:46 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_cmd_line(char **cmd_line)
{
	int i = 0;
	if (cmd_line)
	{
		while (cmd_line[i])
		{
			free(cmd_line[i]);  // 개별 문자열 해제
			i++;
		}
		free(cmd_line);  // 문자열 배열 자체를 해제
	}
}

void free_redirs(t_redir *redir)
{
	t_redir *tmp;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file_name);
		free(tmp);
	}
}

void free_pipeline(t_data *pipeline)
{
	t_data *tmp;
	while (pipeline)
	{
		tmp = pipeline;
		pipeline = pipeline->next;
		free_cmd_line(tmp->cmd_line);
		free_redirs(tmp->redir);
		free(tmp);
	}
}

void get_list(t_list *list, t_data **pipeline_list)
{
    t_node	*p;
    t_data	*data;
	t_data	*tmp;

	data = init_data();
	p = list->head;
    while (p)
    {
        if (p->type == WORD)
        {
            append_cmd(data, p->content);
            p = p->next;
        }
        else if (p->type == REDIR_IN || p->type == REDIR_OUT || p->type == HEREDOC_IN || p->type == HEREDOC_OUT)
        {
            append_redir(data, p);
            p = p->next;
			if (!p || (p->type != WORD))
			{
				printf("Error: Expected word after redirection\n");
				free_pipeline(data);  // 메모리 누수를 막기 위해 추가
				return;  
			}
            p = p->next;
        }
        else if (p->type == PIPE)
        {
			if (!*pipeline_list)
            {
				*pipeline_list = data;
            }
            else
            {
                tmp = (*pipeline_list);
                while (tmp && tmp->next)
				{
                    tmp = tmp->next;
				}
                tmp->next = data;
            }
            data = init_data();
			p = p->next;
        }
		else
        	p = p->next;
    }

	if (data->cmd_line || data->redir)
	{
		if (!*pipeline_list)
		{
			*pipeline_list = data;
		}
		else
		{
			tmp = (*pipeline_list);
			while (tmp && tmp->next)
			{
				tmp = tmp->next;
			}
			tmp->next = data;
		}
	}
	else
	{
		free_pipeline(data);
	}
}

void append_cmd(t_data *data, char *word)
{
    char	**new_cmd_line;
    int 	len;
	int		i;

	len = 0;
    while (data->cmd_line && data->cmd_line[len])
        len++;
    new_cmd_line = (char **)malloc(sizeof(char *) * (len + 2));
    i = 0;
    while (i < len)
    {
        new_cmd_line[i] = data->cmd_line[i];
        i++;
    }
    new_cmd_line[i] = ft_strdup(word);
    new_cmd_line[i + 1] = NULL;

	if (data->cmd_line)  // 메모리 누수를 막기 위해 추가
		free(data->cmd_line);

    data->cmd_line = new_cmd_line;
}

void append_redir(t_data *data, t_node *p)
{
    t_redir *new_redir;
	t_redir	*tmp;

	if (!p->next)
	{
		printf("None file_name after redir\n");
		return ;
	}
	new_redir = init_redir(p);
    if (!data->redir)
        data->redir = new_redir;
    else
    {
    	tmp = data->redir;
        while (tmp && tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_redir;
    }
}
