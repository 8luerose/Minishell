/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:49:33 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/09 04:43:41 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//원본 함수
// int	ft_atouc(char	*str)
// {
// 	long long	i;
// 	long long	num;
// 	int			minus;

// 	i = 0;
// 	minus = 1;
// 	num = 0;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			minus *= -1;
// 		i++;
// 	}
// 	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
// 	{
// 		if (check_ll_range(num, minus, &str[i]))
// 		{
// 			numeric_error(str);
// 			g_stat = 255;
// 			return (g_stat);
// 		}
// 		num *= 10;
// 		num += (str[i] - '0');
// 		i++;
// 	}
// 	num *= minus;
// 	g_stat = (unsigned char)num;
// 	return (g_stat);
// }

long long	parse_num(char *str, int *minus, long long *i)
{
	long long	num;

	num = 0;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			(*minus) *= -1;
		(*i)++;
	}
	while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
	{
		if (check_ll_range(num, *minus, &str[*i]))
		{
			numeric_error(str);
			g_stat = 255;
			return (g_stat);
		}
		num *= 10;
		num += (str[*i] - '0');
		(*i)++;
	}
	return (num);
}

int	ft_atouc(char *str)
{
	long long	i;
	long long	num;
	int			minus;

	i = 0;
	minus = 1;
	num = parse_num(str, &minus, &i);
	num *= minus;
	g_stat = (unsigned char)num;
	return (g_stat);
}

//원본 함수
// int	ft_exit(char **cmd_line)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_line[i])
// 		i++;
// 	if (i > 2)
// 	{
// 		ft_putendl_fd("exit: too many arguments", 2);
// 		g_stat = 1;
// 		return (0);
// 	}
// 	i = 0;
// 	if (!cmd_line[1])
// 		exit(0);
// 	while (cmd_line[1][i])
// 	{
// 		while (cmd_line[1][i] == ' ')
// 			i++;
// 		if (cmd_line[1][i] == '+' || cmd_line[1][i] == '-')
// 			i++;
// 		if (!(cmd_line[1][i] >= '0' && cmd_line[1][i] <= '9'))
// 		{
// 			numeric_error(cmd_line[1]);
// 			exit(255);
// 		}
// 		i++;
// 	}
// 	exit(ft_atouc(cmd_line[1]));
// }

int	is_valid_exit_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
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
	if (!cmd_line[1])
		exit(0);
	if (!is_valid_exit_arg(cmd_line[1]))
	{
		numeric_error(cmd_line[1]);
		exit(255);
	}
	exit(ft_atouc(cmd_line[1]));
}
