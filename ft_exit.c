/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:49:33 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/17 14:43:02 by seojchoi         ###   ########.fr       */
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
	{
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	i = 0;
	if (!cmd_line[1])
		return (0);
	while (cmd_line[1][i])
	{
		while (cmd_line[1][i] == ' ')
			i++;
		if (cmd_line[1][i] == '+' || cmd_line[1][i] == '-')
			i++;
		if (!(cmd_line[1][i] >= '0' && cmd_line[1][i] <= '9'))
		{
			printf("bash: exit: %s: numeric argument required\n", cmd_line[1]);
			return (255);
		}
		i++;
	}
	return (ft_atoi(cmd_line[1]));
}
