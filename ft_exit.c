/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:49:33 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/04 20:24:52 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ll_range(long long num, int minus, char *c)
{
	// max
	if ((num * minus) == 922337203685477580 && (*c > '7' || ft_isdigit(*(c + 1))))
		return (1);
	if ((num * minus) > 922337203685477580 && ft_isdigit(*c))
		return (1);
	// min
	if ((num * minus) == -922337203685477580 && (*c > '8' || ft_isdigit(*(c + 1))))
		return (1);
	if ((num * minus) < -922337203685477580 && ft_isdigit(*c))
		return (1);
	return (0);
}

int	ft_atouc(char	*str)
{
	long long	i;
	long long	num;
	int			minus;

	i = 0;
	minus = 1;
	num = 0;
	if (str[i] == '-')
	{
		minus *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (check_ll_range(num, minus, &str[i]))
		{
			printf("bash: exit: %s: numeric argument required\n", str);
			stat = 255;
			return (stat);
		}
		num *= 10;
		num += (str[i] - '0');
		i++;
	}
	num *= minus;
	stat = (unsigned char)num;
	return (stat);
}

int	ft_exit(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
		i++;
	if (i > 2)
	{
		printf("bash: exit: too many arguments\n");
		stat = 1;
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
			printf("bash: exit: %s: numeric argument required\n", cmd_line[1]);
			exit(255);
		}
		i++;
	}
	exit(ft_atouc(cmd_line[1]));
}
