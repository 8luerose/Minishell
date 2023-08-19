/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:19:15 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/19 20:18:30 by taehkwon         ###   ########.fr       */
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
	char	*error_status_result;

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
	// 태현 버전
	// while (cmd_line[i])
    // {
    //     if (ft_strcmp(cmd_line[i], "$?") == 0)
	// 	{
    //         error_status_result= ft_itoa(stat);
    //         ft_putstr_fd(error_status_result, fd);
    //         free(error_status_result);
    //     }
	// 	else
    //         ft_putstr_fd(cmd_line[i], fd);
    //     if (cmd_line[i + 1])
    //         ft_putstr_fd(" ", fd);
    //     i++;
    // }
	// 원본 코드(서지님 ver)
	while (cmd_line[i])
	{
		ft_putstr_fd(cmd_line[i], fd);
		if (cmd_line[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd);
}
