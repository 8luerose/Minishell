/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 02:03:59 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/09 04:43:58 by taehkwon         ###   ########.fr       */
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
	char	*tmp;
	char	*error;

	error = "exit: ";
	tmp = error;
	error = ft_strjoin(tmp, str);
	tmp = error;
	error = ft_strjoin(tmp, ": numeric argument required");
	ft_putendl_fd(error, 2);
}
