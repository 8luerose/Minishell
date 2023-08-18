/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:05:30 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/15 19:03:55 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(int fd, t_list	*my_envp)
{
	t_node	*iter;

	iter = my_envp->head;
	while (iter)
	{
		ft_putendl_fd(iter->content, fd);
		iter = iter->next;
	}
}
