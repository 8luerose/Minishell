/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:40:29 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/17 12:30:48 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_escape(char *input, int i, char quo)
{
	if (input[i] == '\\')
	{
		if (input[i + 1] && quo != '\'' && (input[i + 1] == 'n' \
			|| input[i + 1] == '\'' || input[i + 1] == '\"'))
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

int	last_check_quo(char quo)
{
	if (quo != 0)
		return (quo_error());
	return (1);
}

void	check_quo(char input, char *quo)
{
	if ((*quo) == 0 && (input == '\'' || input == '\"'))
		*quo = input;
	else if (input == (*quo))
		*quo = 0;
}

void	check_meta_and_quo(char *input, int *i, char *quo, int *size)
{
	if (!is_meta(input[*i]))
		not_meta_case(input, i, quo, size);
	else if (is_meta(input[*i]) && *quo != 0)
		meta_quo_case(input, i, quo, size);
}
