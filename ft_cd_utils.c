/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:22:33 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/06 21:23:06 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_home_error(void)
{
	ft_putendl_fd("cd: HOME not set", 2);
	g_stat = 1;
}

void	parent_dir_error(void)
{
	ft_putendl_fd("cd: error retrieving current directory: getcwd: \
	cannot access parent directories: No such file or directory", 2);
	g_stat = 0;
}