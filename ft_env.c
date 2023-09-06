/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:05:30 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/06 16:52:06 by taehkwon         ###   ########.fr       */
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
