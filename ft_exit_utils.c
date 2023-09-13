/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 02:03:59 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/11 17:34:34 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ll_range(long long n, int minus, char *c)
{
	if ((n * minus) == 922337203685477580 && (*c > '7' || ft_isdigit(*(c + 1))))
		return (1);
	if ((n * minus) > 922337203685477580 && ft_isdigit(*c))
		return (1);
	if ((n * minus) == -922337203685477580 && (*c > '8' \
	|| ft_isdigit(*(c + 1))))
		return (1);
	if ((n * minus) < -922337203685477580 && ft_isdigit(*c))
		return (1);
	return (0);
}

void	numeric_error(char	*str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free(str);
}
