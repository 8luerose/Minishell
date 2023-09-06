/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:49:33 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/06 17:16:50 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ll_range(long long num, int minus, char *c)
{
	if ((num * minus) == 922337203685477580 && (*c > '7' || ft_isdigit(*(c + 1))))
		return (1);
	if ((num * minus) > 922337203685477580 && ft_isdigit(*c))
		return (1);
	if ((num * minus) == -922337203685477580 && (*c > '8' || ft_isdigit(*(c + 1))))
		return (1);
	if ((num * minus) < -922337203685477580 && ft_isdigit(*c))
		return (1);
	return (0);
}

void	numeric_error(char	*str)
{
	char	*tmp;
	char	*error;

	error = "exit: ";
	tmp = error;
	error = ft_strjoin(tmp, str);
	tmp = error;
	error = ft_strjoin(tmp, ": numeric argument required");
	ft_putendl_fd(error, 2);
}

int	ft_atouc(char	*str)
{
	long long	i;
	long long	num;
	int			minus;

	i = 0;
	minus = 1;
	num = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (check_ll_range(num, minus, &str[i]))
		{
			numeric_error(str);
			g_stat = 255;
			return (g_stat);
		}
		num *= 10;
		num += (str[i] - '0');
		i++;
	}
	num *= minus;
	g_stat = (unsigned char)num;
	return (g_stat);
}

int	ft_exit(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_stat = 1;
		return (0);
	}
	i = 0;
	if (!cmd_line[1])
		exit(0);
	while (cmd_line[1][i])
	{
		while (cmd_line[1][i] == ' ')
			i++;
		if (cmd_line[1][i] == '+' || cmd_line[1][i] == '-')
			i++;
		if (!(cmd_line[1][i] >= '0' && cmd_line[1][i] <= '9'))
		{
			numeric_error(cmd_line[1]);
			exit(255);
		}
		i++;
	}
	exit(ft_atouc(cmd_line[1]));
}
