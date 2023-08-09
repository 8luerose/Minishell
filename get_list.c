/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:43:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/09 16:49:08 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_list(t_list *list, t_data *pipeline_list)
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
            p = p->next;  // 파일 이름으로 이동
            if (p)
                p = p->next; //파일 이름에서 한 번 더 건너뛰어준다!
        }
        else if (p->type == PIPE)
        {
            if (!pipeline_list->cmd_line && !pipeline_list->redir)
            {
                pipeline_list->cmd_line = data->cmd_line;
                pipeline_list->redir = data->redir;
            }
            else
            {
                tmp = pipeline_list;
                while (tmp && tmp->next)	//완성된 파이프 리스트 존재해? && 파이프 리스트->next 있어?  
				{
                    tmp = tmp->next;		//있으면 그 뒤로 가! 제일 뒤까지 가보자고~
				}
                tmp->next = data;			//맨 뒤에 data = init_data(); 한 거 추가
            }
            // data = init_data();
            p = p->next;
        }
    }
}

void append_cmd(t_data *data, char *word)
{
    char	**new_cmd_line;
    int 	len;
	int		i;
	int		j;

	len = 0;
    while (data->cmd_line && data->cmd_line[len])
        len++;
    new_cmd_line = malloc(sizeof(char *) * (len + 2));
    i = 0;
    while (i < len)
    {
        new_cmd_line[i] = data->cmd_line[i];
        i++;
    }
    new_cmd_line[i] = ft_strdup(word);
    new_cmd_line[i + 1] = NULL;
    if (data->cmd_line)
	{
		j = 0;
		while (data->cmd_line[j])		//기존 data->cmd_line[] 싹 다 클린
    	{
        	free(data->cmd_line[j]);
        	j++;
    	}
    	free(data->cmd_line);			//기존 data->cmd_line 완전히 비우기
	}
    data->cmd_line = new_cmd_line;		//백업본으로 새로 갈아끼우기
}

void append_redir(t_data *data, t_node *p)
{
    t_redir *new_redir;
	t_redir	*tmp;

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

