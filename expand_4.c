/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:53:16 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/17 13:14:12 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_with_space(char *front, char *expand, char *change, t_node **node)
{
	if (ft_strlen(front) != 0 && expand[0] == ' ')
	{
		(*node)->content = ft_strdup(front);
		add_mid(change, node);
		return (1);
	}
	return (0);
}

char	*split_expand(char *expand, char **front, t_node **node)
{
	int		i;
	char	*tmp;
	char	**change;

	change = ft_split(expand, ' ');
	i = 0;
	while (change[i])
	{
		if (i == 0)
		{
			free((*node)->content);
			if (!start_with_space((*front), expand, change[i], node))
			{
				tmp = ft_strjoin(*front, change[i]);
				(*node)->content = ft_strdup(tmp);
				free(tmp);
			}
			free(*front);
		}
		else
			add_mid(change[i], node);
		i++;
	}
	free_all(change);
	return (ft_strdup((*node)->content));
}

void	join_expand(char **new_content, char *expand, int *i, int size)
{
	char	*tmp;

	tmp = ft_strdup(*new_content);
	free(*new_content);
	(*new_content) = ft_strjoin(tmp, expand);
	free(tmp);
	if (*expand)
		free(expand);
	(*i) += size;
}

void	ch_iter(char **new, char *tmp_content, t_node **iter, t_list *envp)
{
	int		i;
	int		size;
	char	quo;
	char	*expand;

	i = 0;
	quo = 0;
	while (tmp_content[i])
	{
		if (start_quo(&quo, tmp_content[i]) || end_quo(&quo, tmp_content[i]))
			i++;
		else if (can_expand(&size, (*iter), quo, &tmp_content[i]))
		{
			expand = get_expand(i, size, tmp_content, envp);
			if (unsplitable(quo, iter))
				join_expand(new, expand, &i, size);
			else if (splitable(quo, expand, &i, size))
			{
				(*new) = split_expand(expand, new, iter);
				end_space(tmp_content[i], iter, new, expand);
			}
		}
		else
			join_content(new, tmp_content, &i, quo);
	}
}

void	expand_and_delete_quo(t_list *envp, t_list *list)
{
	t_node		*iter;
	char		*new_content;
	char		*tmp_content;

	iter = list->head;
	while (iter)
	{
		new_content = ft_strdup("");
		tmp_content = ft_strdup(iter->content);
		ch_iter(&new_content, tmp_content, &iter, envp);
		free(tmp_content);
		free(iter->content);
		iter->content = new_content;
		iter = iter->next;
	}
}
