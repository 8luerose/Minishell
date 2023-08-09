/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:43:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/09 21:05:21 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_list(t_list *list, t_data **pipeline_list)
{
    t_node	*p;
    t_data	*data;
	t_data	*tmp;

	data = init_data();
	p = list->head;
    while (p)
    {
		printf("Current p content: %s\n", p->content);

        if (p->type == WORD)
        {
            append_cmd(data, p->content);
            p = p->next;
        }
        else if (p->type == REDIR_IN || p->type == REDIR_OUT || p->type == HEREDOC_IN || p->type == HEREDOC_OUT)
        {
			printf("After0_ append_redir\n"); 
            append_redir(data, p);
			printf("After1_ append_redir\n"); // append_redir 이후 출력
            p = p->next;  // 파일 이름으로 이동
            if (p)
                p = p->next; //파일 이름에서 한 번 더 건너뛰어준다!
			printf("After2_ file_name\n"); // append_redir 이후 출력
        }
        else if (p->type == PIPE)
        {
			printf("**0 p content: %s\n", p->content);
            // if (!pipeline_list->cmd_line && !pipeline_list->redir)
			if (!*pipeline_list)
            {
				printf("**1-1 p content: %s\n", p->content);
                // (*pipeline_list)->cmd_line = data->cmd_line;
                // (*pipeline_list)->redir = data->redir;
				*pipeline_list = data;
				printf("**1-2 p content: %s\n", p->content);
            }
            else
            {
				printf("**2-1 p content: %s\n", p->content);
                tmp = (*pipeline_list);
                while (tmp && tmp->next)	//완성된 파이프 리스트 존재해? && 파이프 리스트->next 있어?  
				{
                    tmp = tmp->next;		//있으면 그 뒤로 가! 제일 뒤까지 가보자고~
				}
                tmp->next = data;			//맨 뒤에 data = init_data(); 한 거 추가
				printf("**2-2 p content: %s\n", p->content);
            }
            data = init_data();
			printf("pipe end point_1 p content: %s\n", p->content);
			p = p->next;
			printf("pipe end point_2 p content: %s\n", p->content);
        }
		else
        	p = p->next;
    }
	// while (tmp && tmp->next)	//완성된 파이프 리스트 존재해? && 파이프 리스트->next 있어?  
	// {
    //     tmp = tmp->next;		//있으면 그 뒤로 가! 제일 뒤까지 가보자고~
	// }
	// tmp = NULL;
}

void append_cmd(t_data *data, char *word)
{
    char	**new_cmd_line;
    int 	len;
	int		i;
	// int		j;

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
    // if (data->cmd_line)
	// {
	// 	j = 0;
	// 	while (data->cmd_line[j])		//기존 data->cmd_line[] 싹 다 클린
    // 	{
    //     	// free(data->cmd_line[j]);
    //     	j++;
    // 	}
    // 	// free(data->cmd_line);			//기존 data->cmd_line 완전히 비우기
	// }
    data->cmd_line = new_cmd_line;		//백업본으로 새로 갈아끼우기
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

