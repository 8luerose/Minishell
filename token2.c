// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   token2.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/05 18:08:38 by taehkwon          #+#    #+#             */
// /*   Updated: 2023/08/05 18:40:47 by taehkwon         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	get_group_token(t_list *list)
// {
// 	t_cmd	*cmd;
// 	t_redir	*redir;
// 	t_data	*data;
// 	t_node	*tmp;
// 	t_node	*tmp2;
// 	char	*tmp_redir;

// 	cmd = (t_cmd *)malloc(sizeof(cmd));
// 	redir = (t_redir *)malloc(sizeof(redir));
// 	data = (t_data *)malloc(sizeof(data));
// 	group_node_init(cmd, redir, data);
// 	tmp = list->head;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->content, "<") == 0 && ft_strcmp(tmp->content, ">") == 0)
// 		{
// 			if (tmp->next)
// 			{
// 				tmp2 = tmp->next;
// 				if (ft_strcmp(tmp->content, tmp2->content) == 0 \
// 					&& ft_strcmp(tmp->content, tmp2->content) == 0)
// 					{
						
// 					}
// 			}
// 			if ()
// 		}
// 		else
// 		{
// 			cmd->cmd_line[0] = ft_strdup(tmp->content);
// 			if (tmp->next)
// 			{
// 				tmp2 = tmp->next;
// 				if (!(ft_strcmp(tmp2->content, "<") == 0 && ft_strcmp(tmp2->content, "<") == 0))
// 				{
// 					cmd->cmd_line[1] = ft_strdup(tmp2->content);
// 					tmp = tmp->next;
// 				}
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }

// void	group_node_init(t_cmd *cmd, t_redir *redir, t_data *data)
// {
// 	cmd->cmd_line = NULL;
// 	cmd->next = NULL;

// 	redir->redir = NULL;
// 	redir->file_name = NULL;
// 	redir->next = NULL;
	
// 	data->cmd = cmd;
// 	data->redirect = redir;
// 	data->next = NULL;
// }