/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:20:34 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/04 20:10:52 by taehkwon         ###   ########.fr       */
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

// void	command_error(char *cmd)
// {
// 	int	size;

// 	write(2, "bash: ", 6);
// 	size = cnt_str(cmd);
// 	write(2, cmd, size);
// 	write(2, ": command not found\n", 20);
// 	stat = 127;
// 	exit(127);
// }

int	file_error(char *file_name)
{
	write(2, "bash: ", 6);
	perror(file_name);
	stat = 1;
	return (stat);
}

int	system_error(void)
{
	char	*error;

	error = "bash";
	perror(error);
	stat = 1;
	return (stat);
}

void	command_error(char	*cmd)
{
	if (access(cmd, F_OK) < 0)
	{
		stat = 127;
		ft_putendl_fd("No such file or directory", 2);  // 수정
	}
	else if (access(cmd, X_OK) < 0)
	{
		stat = 126;
		ft_putendl_fd("Permission denied", 2);  // 수정
	}
}
