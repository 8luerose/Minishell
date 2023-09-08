/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 06:01:47 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/09 06:03:47 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_and_increment(char **new_content, char *content, int *i)
{
	(*new_content) = ft_strjoin_c((*new_content), content[*i]);
	(*i)++;
}

void	join_new_content(char **new_content, char *content, int *i, char quo)
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
		else if (quo == '\'')
			append_and_increment(new_content, content, i);
	}
	else
		append_and_increment(new_content, content, i);
}

char	*get_expand(int i, int size, char *tmp_content, t_list *envp)
{
	char	*key;
	char	*expand;

	key = make_key(tmp_content, i + 1, size - 1);
	expand = get_env(key, envp);
	free(key);
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
