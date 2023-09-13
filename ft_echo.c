/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:19:15 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/10 15:16:02 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

void	ft_echo(int fd, char **cmd_line)
{
	int		i;
	int		is_n;

	i = 1;
	is_n = 0;
	while (cmd_line[i])
	{
		if (find_n(cmd_line[i]))
			is_n = 1;
		else
			break ;
		i++;
	}
	while (cmd_line[i])
	{
		ft_putstr_fd(cmd_line[i], fd);
		if (cmd_line[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (is_n == 0)
		ft_putstr_fd("\n", fd);
	g_stat = 0;
}
