/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:49:33 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/27 14:04:49 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
		i++;
	printf("exit\n");
	if (i > 2)
		return (printf("bash: exit: too many arguments\n") && 1);
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
	exit(ft_atoi(cmd_line[1]));
}
