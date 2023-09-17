/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:20:34 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/17 15:05:13 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	quo_error(void)
{
	ft_putendl_fd("syntax error: quotation marks don't match", 2);
	g_stat = 258;
	return (0);
}

int	file_error(char *file_name)
{
	perror(file_name);
	g_stat = 1;
	return (g_stat);
}

void	command_error(char	*cmd, char *access_path)
{
	struct stat	statbuf;

	stat(cmd, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		g_stat = 126;
		exit(126);
	}
	else
	{
		if (access(access_path, F_OK))
			g_stat = 127;
		else if (access(access_path, X_OK))
			g_stat = 126;
		perror(cmd);
		exit(g_stat);
	}
}
