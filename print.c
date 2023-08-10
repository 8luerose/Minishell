/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:03:48 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/11 03:06:19 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_redir_test(t_redir *redir) 
{
    while (redir) {
        printf("Redirection: %s -> %s\n", redir->redir, redir->file_name);
        redir = redir->next;
    }
}

void print_data_test(t_data *data) 
{
    while (data) {
        if (data->cmd_line) {
            printf("Command: ");
            char **cmd = data->cmd_line;
            while (*cmd) {
                printf("%s ", *cmd);
                cmd++;
            }
            printf("\n");
        }
        if (data->redir) {
            print_redir_test(data->redir);
        }
        data = data->next;
        if (data) {
            printf("---------\n"); // 각 파이프라인의 명령을 구분하기 위해 사용
        }
    }
}

void print_redir(t_redir *redir) 
{
    while (redir) {
        printf("%s %s ", redir->redir, redir->file_name);
        redir = redir->next;
    }
}

void print_data(t_data *data) 
{
    while (data) {
        if (data->cmd_line) {
            char **cmd = data->cmd_line;
            while (*cmd) {
                printf("%s ", *cmd);
                cmd++;
            }
        }
        if (data->redir) {
            print_redir(data->redir);
        }
        data = data->next;
        if (data) {
            printf("| "); // 각 파이프라인의 명령을 구분하기 위해 사용
        }
    }
    printf("\n");
}