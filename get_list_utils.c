/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 06:11:20 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/17 11:55:48 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_cmd(t_data *new_data, char *word)
{
	char	**new_cmd_line;
	int		len;
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

void	append_redir(t_data *new_data, t_node *p)
{
	t_redir	*new_redir;
	t_redir	*tmp;

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
