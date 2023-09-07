/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 03:42:56 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/07 12:47:51 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_limiter(char *str, char *limiter)
{
	int	i;

	i = 0;
	if (!limiter)
		return (1);
	while (str[i] && limiter[i])
	{
		if (str[i] != limiter[i])
			return (0);
		i++;
	}
	if (!(str[i] == '\0' && limiter[i] == '\0'))
		return (0);
	return (1);
}
