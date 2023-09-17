/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 06:01:03 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/12 11:59:31 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_expand(char *expand)
{
	if (expand)
		free(expand);
}

void	end_space(char cont, t_node **iter, char **new_con, char *expand)
{
	int		j;

	j = 0;
	while (expand[j])
		j++;
	if (expand[j - 1] == ' ' && cont)
	{
		add_mid("", iter);
		free(*new_con);
		(*new_con) = ft_strdup("");
	}
	free_expand(expand);
}

int	start_quo(char	*quo, char tmp_content)
{
	if ((*quo) == 0
		&& (tmp_content == '\'' || tmp_content == '\"' ))
	{
		(*quo) = tmp_content;
		return (1);
	}
	return (0);
}

int	end_quo(char *quo, char tmp_content)
{
	if (tmp_content == (*quo))
	{
		(*quo) = 0;
		return (1);
	}
	return (0);
}

int	can_expand(int *size, t_node *iter, char quo, char *tmp_content)
{
	if ((*tmp_content) == '$')
	{
		(*size) = check_envp_size(tmp_content);
		if ((*size) > 0 && quo != '\'')
		{
			if (iter->prev && iter->prev->type == HEREDOC_IN)
				return (0);
			return (1);
		}
	}
	return (0);
}
