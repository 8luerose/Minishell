/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:20:34 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/07 19:10:23 by taehkwon         ###   ########.fr       */
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
	char		*tmp;
	char		*error;
	struct stat	statbuf;

	stat(cmd, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		error = ": is a directory";
		tmp = error;
		error = ft_strjoin(cmd, tmp);
		ft_putendl_fd(error, 2);
		free(error);
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
