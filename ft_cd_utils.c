/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:22:33 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/11 16:34:49 by seojchoi         ###   ########.fr       */
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

void	cd_error(char	**cmd_line)
{
	char	*tmp;
	char	*error;

	error = ft_strdup("cd: ");
	tmp = ft_strdup(error);
	free(error);
	error = ft_strjoin(tmp, cmd_line[1]);
	free(tmp);
	perror(error);
	free(error);
	g_stat = 1;
}
