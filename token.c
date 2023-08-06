/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:05 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 20:28:32 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	get_token(char *input, t_list *list)
{
	int		i;
	char	*buf;
	char	*tmp;
	t_flag	flag;

	i = 0;
	flag.quo = 0;
	flag.env = 0;
	flag.env_with_quo = 0;
	buf = ft_strdup("");
	while (input[i])
	{
		if (!is_meta(input[i]))
		{
			if (flag.quo == 0)
			{
				if (input[i] == '\"')
					flag.quo = DOUBLE_Q;
				else if (input[i] == '\'')
					flag.quo = SINGLE_Q;
				else if (input[i] == '$')
					flag.env = 1;
			}
			else
			{
				if (input[i] == '\"' && flag.quo == DOUBLE_Q)
					flag.quo = 0;
				else if (input[i] == '\'' && flag.quo == SINGLE_Q)
					flag.quo = 0;
			}
			if (flag.quo == DOUBLE_Q && input[i] == '$')
				flag.env_with_quo = 1;
			tmp = buf;
			buf = ft_strjoin_c(tmp, input[i]);
			free(tmp);
		}
		else if (is_meta(input[i]) && flag.quo > 0)
		{
			tmp = buf;
			buf = ft_strjoin_c(tmp, input[i]);
			free(tmp);
		}
		else
		{
			if (flag.quo)
				exit(1);
			if (buf[0] != 0)
			{
				make_node(buf, flag, list);
				flag.env = 0;
				flag.env_with_quo = 0;
			}
			if (input[i] != ' ')
			{
				if (input[i + 1] && ((input[i] == '<' && input[i+1] == '<') || (input[i] == '>' && input[i+1] == '>'))) 
				{
					tmp = ft_strndup(&input[i], 2);
					i++;
				}
				else
				{
					tmp = ft_strndup(&input[i], 1);
				}
				buf = ft_strjoin_c(tmp, input[i]);
				free(tmp);
				make_node(buf, flag, list);
			}
			free(buf);
			buf = ft_strdup("");
		}
		i++;
	}
	if (flag.quo)
		exit(1);
	make_node(buf, flag, list);
	free(buf);
}
