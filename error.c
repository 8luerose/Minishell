/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:20:34 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/17 17:20:27 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	command_error(char *cmd)
{
	int	size;

	write(2, "bash: ", 6);
	size = cnt_str(cmd);
	write(2, cmd, size);
	write(2, ": command not found\n", 20);
	stat = 127;
	exit(1);
}

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
