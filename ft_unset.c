/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:16 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/10 16:46:45 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_list *my_envp, t_node *iter)
{
	if (iter->prev != NULL)
		iter->prev->next = iter->next;
	else
		my_envp->head = iter->next;
	if (iter->next != NULL)
		iter->next->prev = iter->prev;
	else
		my_envp->tail = iter->prev;
	free(iter->content);
	free(iter);
}

void	unset_node(t_list *my_envp, char *key)
{
	t_node	*iter;

	iter = my_envp->head;
	while (iter)
	{
		if (ft_strncmp(key, iter->content, ft_strlen(key)) == 0)
		{
			delete_node(my_envp, iter);
			break ;
		}
		iter = iter->next;
	}
}

void	ft_unset(t_list	*my_envp, char **cmd_line)
{
	int		i;
	char	*key;

	i = 1;
	while (cmd_line[i])
	{
		key = ft_strjoin(cmd_line[i], "=");
		unset_node(my_envp, key);
		free(key);
		i++;
	}
}
