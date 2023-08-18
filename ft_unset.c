/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:16 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/17 14:35:45 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list	*my_envp, char **cmd_line)
{
	int		i;
	char	*key;
	t_node	*iter;

	i = 1;
	while (cmd_line[i])
	{
		key = ft_strjoin(cmd_line[i], "=");
		iter = my_envp->head;
		while (iter)
		{
			if (ft_strncmp(key, iter->content, ft_strlen(key)) == 0)
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
				break ;
			}
			iter = iter->next;
		}
		i++;
	}
}
