/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:40:29 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/07 12:48:58 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_escape(char *input, int i, char quo)
{
	if (input[i] == '\\')
	{
		if (input[i + 1] && quo != '\'' &&  (input[i + 1] == 'n' || input[i + 1] == '\'' || input[i + 1] == '\"'))
			return (1);
	}
	return (0);
}

int	is_meta(char c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
