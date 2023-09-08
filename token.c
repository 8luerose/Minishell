/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:05 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/09 06:09:43 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_escape(char *input, int *i, char **buf)
{
	char	*tmp;

	tmp = *buf;
	*buf = ft_strjoin_c(tmp, input[*i]);
	free(tmp);
	(*i)++;
}

void	get_quote(char *input, int *i, char **buf, char *quo)
{
	char	*tmp;

	if (*quo == 0 && (input[*i] == '\'' || input[*i] == '\"'))
		*quo = input[*i];
	else if (input[*i] == *quo)
		*quo = 0;
	tmp = *buf;
	*buf = ft_strjoin_c(tmp, input[*i]);
	free(tmp);
}

void	get_meta(char *input, int *i, char **buf, t_list *list)
{
	char	*tmp;

	if ((*buf)[0] != 0)
		make_node(*buf, list);
	if (input[*i] != ' ' && input[*i] != '\t')
	{
		if (input[*i + 1]
			&& ((input[*i] == '<' && input[*i + 1] == '<') \
			|| (input[*i] == '>' && input[*i + 1] == '>')))
		{
			tmp = ft_strndup(&input[*i], 2);
			(*i)++;
		}
		else
			tmp = ft_strndup(&input[*i], 1);
		(*buf) = ft_strjoin_c(tmp, input[*i]);
		free(tmp);
		make_node(*buf, list);
	}
	free(*buf);
	(*buf) = ft_strdup("");
}

int	quo_error_check(char *buf, char quo, t_list *list)
{
	if (quo != 0)
		return (quo_error());
	if (buf[0] != 0)
		make_node(buf, list);
	free(buf);
	return (1);
}

int	get_token(char *input, t_list *list)
{
	int		i;
	char	quo;
	char	*buf;

	i = 0;
	quo = 0;
	buf = ft_strdup("");
	while (input[i])
	{
		if (!is_meta(input[i]))
		{
			if (is_escape(input, i, quo))
				get_escape(input, &i, &buf);
			else
				get_quote(input, &i, &buf, &quo);
		}
		else if (is_meta(input[i]) && quo != 0)
			get_quote(input, &i, &buf, &quo);
		else
			get_meta(input, &i, &buf, list);
		i++;
	}
	return (quo_error_check(buf, quo, list));
}
