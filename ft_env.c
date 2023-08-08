/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:42:58 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/08 15:49:21 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list	*my_envp)
{
	t_node	*iter;

	iter = my_envp->head;
	while (iter)
	{
		printf("%s\n", iter->content);
		iter = iter->next;
	}
}
