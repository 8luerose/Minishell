/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_token2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 02:02:34 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/08 02:32:49 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void append_to_cmd(t_cmd **cmd, char *content);
void append_to_redir(t_redir **redir, char *content, char *filename);
void append_data(t_data **data_head, t_data *new_data);
void free_cmd(t_cmd *cmd);
void free_redir(t_redir *redir);

void append_data(t_data **data_head, t_data *new_data)
{
    t_data *temp = *data_head;

    if (!*data_head)
    {
        *data_head = new_data;
        return;
    }

    while (temp->next)
        temp = temp->next;

    temp->next = new_data;
}

void free_cmd(t_cmd *cmd)
{
    int i = 0;

    if (!cmd)
        return;

    if (cmd->cmd_line)
    {
        while (cmd->cmd_line[i])
        {
            free(cmd->cmd_line[i]);
            i++;
        }
        free(cmd->cmd_line);
    }
    free(cmd);
}

void free_redir(t_redir *redir)
{
    int i = 0;

    if (!redir)
        return;

    if (redir->redir)
    {
        while (redir->redir[i])
        {
            free(redir->redir[i]);
            i++;
        }
        free(redir->redir);
    }

    if (redir->file_name)
        free(redir->file_name);

    free(redir);
}

void append_to_cmd(t_cmd **cmd, char *content)
{
    char **new_cmd_line;
    int i = 0;

    if (!*cmd)
    {
        *cmd = (t_cmd *)malloc(sizeof(t_cmd));
        (*cmd)->cmd_line = NULL;
    }

    while ((*cmd)->cmd_line && (*cmd)->cmd_line[i])
        i++;
    new_cmd_line = (char **)malloc(sizeof(char *) * (i + 2));

    int j = 0;
    while (j < i)
    {
        new_cmd_line[j] = (*cmd)->cmd_line[j];
        j++;
    }
    new_cmd_line[i] = ft_strdup(content);
    new_cmd_line[i + 1] = NULL;

    free((*cmd)->cmd_line);
    (*cmd)->cmd_line = new_cmd_line;
}

void append_to_redir(t_redir **redir, char *content, char *filename)
{
    char **new_redir;
    int i = 0;

    if (!*redir)
    {
        *redir = (t_redir *)malloc(sizeof(t_redir));
        (*redir)->redir = NULL;
        (*redir)->file_name = NULL;
        (*redir)->next = NULL;
    }

    while ((*redir)->redir && (*redir)->redir[i])
        i++;
    new_redir = (char **)malloc(sizeof(char *) * (i + 2));

    int j = 0;
    while (j < i)
    {
        new_redir[j] = (*redir)->redir[j];
        j++;
    }
    new_redir[i] = ft_strdup(content);
    new_redir[i + 1] = NULL;

    free((*redir)->redir);
    (*redir)->redir = new_redir;
    (*redir)->file_name = ft_strdup(filename);
}

void group_tokens(t_list *tokens, t_data **data_list)
{
    t_data *current_data = NULL;
    t_cmd *current_cmd = NULL;
    t_redir *current_redir = NULL;
    t_type type;
    t_node *node = tokens->head;

    while (node)
    {
        type = token_type(node->content);

        switch (type)
        {
        case WORD:
            if (!current_cmd)
            {
                current_cmd = (t_cmd *)malloc(sizeof(t_cmd));
                if (!current_cmd)
                    return;
                current_cmd->cmd_line = NULL;
            }
            append_to_cmd(&current_cmd, node->content);
            break;

        case REDIRECTION:
            if (!current_redir)
            {
                current_redir = (t_redir *)malloc(sizeof(t_redir));
                if (!current_redir)
                {
                    free_cmd(current_cmd);
                    return;
                }
                current_redir->redir = NULL;
                current_redir->file_name = NULL;
                current_redir->next = NULL;
            }
            if (!node->next) // 파일 이름이 없는 경우 처리
            {
                free_cmd(current_cmd);
                free_redir(current_redir);
                return;
            }
            append_to_redir(&current_redir, node->content, node->next->content);
            node = node->next;
            break;

        case PIPE:
            if (current_cmd || current_redir)
            {
                current_data = (t_data *)malloc(sizeof(t_data));
                if (!current_data)
                {
                    free_cmd(current_cmd);
                    free_redir(current_redir);
                    return;
                }
                current_data->cmd = current_cmd;
                current_data->redirect = current_redir;
                current_data->next = NULL;
                append_data(data_list, current_data);
            }
            current_cmd = NULL;
            current_redir = NULL;
            break;

        default:
            break;
        }

        node = node->next;
    }

    if (current_cmd || current_redir)
    {
        current_data = (t_data *)malloc(sizeof(t_data));
        if (!current_data)
        {
            free_cmd(current_cmd);
            free_redir(current_redir);
            return;
        }
        current_data->cmd = current_cmd;
        current_data->redirect = current_redir;
        current_data->next = NULL;
        append_data(data_list, current_data);
    }
}

// int main(void)
// {
//     t_list tokens;
//     t_data *data_list = NULL;

//     // Assuming tokens list is populated
//     group_tokens(&tokens, &data_list);
//     // Rest of the code...

//     return 0;
// }
