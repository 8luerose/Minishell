/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:06:37 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/17 12:31:03 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_token(t_list *list, char *input, int start, int size)
{
	char	*content;

	content = ft_substr(input, start, size);
	make_node(content, list);
	free(content);
}

void	not_meta_case(char *input, int *i, char *quo, int *size)
{
	if (is_escape(input, *i, *quo))
	{
		*size += 2;
		*i += 2;
	}
	else
	{
		check_quo(input[*i], quo);
		*size += 1;
		*i += 1;
	}
}

void	meta_quo_case(char *input, int *i, char *quo, int *size)
{
	check_quo(input[*i], quo);
	*size += 1;
	*i += 1;
}

void	handle_meta_token(t_list *list, char *input, int *i, int *size)
{
	if (input[*i] == ' ' || input[*i] == '\t')
	{
		*size = 0;
		(*i)++;
	}
	else
	{
		if (input[*i + 1] && ((input[*i] == '<' && input[*i + 1] == '<') \
			|| (input[*i] == '>' && input[*i + 1] == '>')))
			*size = 2;
		else
			*size = 1;
		make_token(list, input, *i, *size);
	}
}

int	get_token(char *input, t_list *list)
{
	int		i;
	int		size;
	int		start;
	char	quo;

	i = 0;
	size = 0;
	quo = 0;
	start = i;
	while (input[i])
	{
		check_meta_and_quo(input, &i, &quo, &size);
		if (is_meta(input[i]) && quo == 0)
		{
			if (i > 0 && !is_meta(input[i - 1]))
				make_token(list, input, start, size);
			handle_meta_token(list, input, &i, &size);
			start = i + size;
			i += size;
			size = 0;
		}
	}
	if (i > 0 && !is_meta(input[i - 1]))
		make_token(list, input, start, size);
	return (last_check_quo(quo));
}
