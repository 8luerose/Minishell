/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:21:20 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/31 20:49:08 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_list(t_list *list, t_data **pipe_data)
{
	t_node	*p;
	t_data	*new_data;
	t_data	*tmp;

	new_data = init_new_data();
	p = list->head;
    while (p)
    {
        if (p->type == WORD)
        {
            append_cmd(new_data, p->content);
            p = p->next;
        }
        else if (p->type == REDIR_IN || p->type == REDIR_OUT \
			|| p->type == HEREDOC_IN || p->type == HEREDOC_OUT)
        {
            append_redir(new_data, p);
            p = p->next;
			if (!p || (p->type != WORD))
			{
				printf("ERROR: NO WORD after redirection\n");
				free_pipeline(new_data);
				exit(1);
			}
            p = p->next;
        }
        else if (p->type == PIPE)
        {
			if (!*pipe_data)
            {
				*pipe_data = new_data;		//새로 만든 data 연결
            }
            else
            {
                tmp = (*pipe_data);
                while (tmp && tmp->next)
				{
                    tmp = tmp->next;
				}
                tmp->next = new_data;		//기존꺼 맨 뒤에 새로 만든 data 연결
            }
            new_data = init_new_data();
			p = p->next;
        }
		else	//이거 빼면 무한루프 생길 수 있음, 불필요한 타입이 리스트에 존재하더라도 우선 패스하고 끝은 나야함
        	p = p->next;
    }

	if (new_data->cmd_line || new_data->redir)		// ~ | ls 즉, 맨 마지막 파이프 뒤에꺼
	{
		if (!*pipe_data)
		{
			*pipe_data = new_data;
		}
		else
		{
			tmp = (*pipe_data);
			while (tmp && tmp->next)
			{
				tmp = tmp->next;
			}
			tmp->next = new_data;
		}
	}
	else											//| ' ' 즉, 마지막 데이터 없으면 만들어진 data 그냥 free 
	{
		free_pipeline(new_data);
	}
}

void append_cmd(t_data *new_data, char *word)
{
    char	**new_cmd_line;
    int 	len;
	int		i;

	len = 0;
    while (new_data->cmd_line && new_data->cmd_line[len])
        len++;
    new_cmd_line = (char **)malloc(sizeof(char *) * (len + 2));
    i = 0;
    while (i < len)
    {
        new_cmd_line[i] = new_data->cmd_line[i];
        i++;
    }
    new_cmd_line[i] = ft_strdup(word);
    new_cmd_line[i + 1] = NULL;

	if (new_data->cmd_line)
		free(new_data->cmd_line);

    new_data->cmd_line = new_cmd_line;
}

void append_redir(t_data *new_data, t_node *p)
{
    t_redir	*new_redir;
	t_redir	*tmp;

	if (!p->next)
	{
		printf("None 'file_name' after redir\n");
		exit(1);
	}
	new_redir = init_new_redir(p);
    if (!new_data->redir)
        new_data->redir = new_redir;
    else
    {
    	tmp = new_data->redir;
        while (tmp && tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_redir;
    }
}

// void append_cmd(t_data *new_data, char *word)
// {
//     char	**new_cmd_line;
//     int 	len;
// 	int		i;

// 	len = 0;
//     while (new_data->cmd_line && new_data->cmd_line[len])
//         len++;
//     new_cmd_line = (char **)malloc(sizeof(char *) * (len + 2));
//     i = 0;
//     while (i < len)
//     {
//         new_cmd_line[i] = new_data->cmd_line[i];
//         i++;
//     }
//     new_cmd_line[i] = ft_strdup(word);
//     new_cmd_line[i + 1] = NULL;

// 	if (new_data->cmd_line)
// 		free(new_data->cmd_line);

//     new_data->cmd_line = new_cmd_line;
// }

// void append_redir(t_data *new_data, t_node *p)
// {
//     t_redir	*new_redir;
// 	t_redir	*tmp;

// 	if (!p->next)
// 	{
// 		printf("None 'file_name' after redir\n");
// 		exit(1);
// 	}
// 	new_redir = init_new_redir(p);
//     if (!new_data->redir)
//         new_data->redir = new_redir;
//     else
//     {
//     	tmp = new_data->redir;
//         while (tmp && tmp->next)
//         {
//             tmp = tmp->next;
//         }
//         tmp->next = new_redir;
//     }
// }