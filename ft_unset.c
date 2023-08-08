/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:16 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/08 15:49:02 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_unset(t_list *my_envp, char *str)
// {
// 	char	*key;
// 	t_node	*tmp;
// 	t_node	*iter;

// 	key = ft_strjoin(str, "=");
// 	iter = my_envp->head;
// 	while (iter)
// 	{
// 		if (ft_strncmp(key, iter->content, ft_strlen(key)) == 0)
// 		{
// 			iter->prev->next = iter->next;
// 			iter->next->prev = iter->prev;
// 			free(iter->content);
// 			free(iter);
// 			break ;
// 		}
// 		iter = iter->next;
// 	}
// }
