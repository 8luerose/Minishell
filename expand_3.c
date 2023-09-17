/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 06:01:47 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/10 18:35:38 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_and_increment(char **new_content, char *content, int *i)
{
	char	*tmp;

	tmp = *new_content;
	(*new_content) = ft_strjoin_c(tmp, content[*i]);
	free(tmp);
	(*i)++;
}

void	join_content(char **new_content, char *content, int *i, char quo)
{
	if (content[*i] == '\\')
	{
		if (quo == 0 && content[(*i) + 1] && (content[(*i) + 1] == 'n' \
			|| content[(*i) + 1] == '\'' || content[(*i) + 1] == '\"'))
			(*i)++;
		else if (quo == '\"')
		{
			if (content[(*i) + 1] && content[(*i) + 1] == '\"')
				(*i)++;
			else
				append_and_increment(new_content, content, i);
		}
	}
	append_and_increment(new_content, content, i);
}

char	*get_expand(int i, int size, char *tmp_content, t_list *envp)
{
	char	*key;
	char	*expand;

	key = make_key(tmp_content, i + 1, size - 1);
	expand = get_env(key, envp);
	return (expand);
}

int	unsplitable(char quo, t_node **iter)
{
	if (quo == '\"' || (quo == 0 && (*iter)->prev \
	&& (((*iter)->prev->type == REDIR_IN) \
	|| ((*iter)->prev->type == REDIR_OUT) \
	|| ((*iter)->prev->type == HEREDOC_OUT))))
		return (1);
	return (0);
}

int	splitable(char quo, char *expand, int *i, int size)
{
	if (quo == 0)
	{
		(*i) += size;
		if (ft_strlen(expand) != 0)
			return (1);
	}
	return (0);
}
