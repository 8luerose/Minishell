/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:19:15 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/06 17:16:21 by taehkwon         ###   ########.fr       */
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
	int		res;
	int		flag;

	i = 1;
	flag = 0;
	while (cmd_line[i])
	{
		res = find_n(cmd_line[i]);
		if (res == 1)
			flag = 1;
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
	if (flag == 0)
		ft_putstr_fd("\n", fd);
	g_stat = 0;
}
