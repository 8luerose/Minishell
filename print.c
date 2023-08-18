/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:21:55 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/11 12:21:59 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redir(t_redir *redir)
{
	t_redir	*p;

	p = redir;
    while (p)
	{
        printf("%s %s ", p->redir, p->file_name);
        p = p->next;
    }
}

void print_result(t_data *data)
{
	char	**now_cmd;

    while (data)
	{
        if (data->cmd_line)
		{
            now_cmd = data->cmd_line;
            while (*now_cmd)				//cmd[0] -> cmd[1]
			{
                printf("%s ", *now_cmd);
                now_cmd++;
            }
        }
        if (data->redir)
		{
            print_redir(data->redir);
        }
        data = data->next;
        if (data)
            printf("| "); // 각 파이프라인 구분하기 위해 사용
    }
	printf("\n");
}

void	print_type(t_list *list)
{
	t_node	*test;

	test = list->head;
	while (test)
	{
		printf("%s   (type: %d)\n", test->content, test->type);
		test = test->next;
	}
}





////////////////////////////////////////////////////////////////////////////////
static void print_redir_test(t_redir *redir) 
{
	t_redir	*p;

	p = redir;
    while (p)
	{
        printf("Redirection: %s  %s\n", p->redir, p->file_name);
        p = p->next;
    }
}

void print_result_test(t_data *data) 
{
	char	**now_cmd;

    while (data)
	{
        if (data->cmd_line)
		{
            printf("Command: ");
            now_cmd = data->cmd_line;
            while (*now_cmd)
			{
                printf("%s ", *now_cmd);
                now_cmd++;
            }
            printf("\n");
        }
        if (data->redir)
		{
            print_redir_test(data->redir);
        }
        data = data->next;
        if (data)
		{
            printf("|\n"); // 각 파이프라인의 명령을 구분하기 위해 사용
        }
    }
	printf("\ntest completed!\n\n");
}
