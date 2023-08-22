/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:30:51 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/19 17:47:07 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_envp(char	*content)
{
	int		i;
	char	*new;

	i = 0;
	if ((content[i + 1] >= 'a' && content[i + 1] <= 'z')
		|| (content[i + 1] >= 'A' && content[i + 1] <= 'Z')
		|| (content[i + 1] >= '0' && content[i + 1] <= '9')
		|| content[i + 1] == '_')
		i++;
	else
		return (-1);
	while (content[i])
	{
		if (!((content[i] >= 'a' && content[i] <= 'z')
				|| (content[i] >= 'A' && content[i] <= 'Z')
				|| (content[i] >= '0' && content[i] <= '9')
				|| content[i] == '_'))
			break ;
		i++;
	}
	new = ft_substr(content, 1, i - 1);
	return (i);
}

char	*get_env(char *key, t_list *envp)
{
	char	*content;
	t_node	*iter;

	content = NULL;
	key = ft_strjoin(key, "=");
	iter = envp->head;
	while (iter)
	{
		if (ft_strncmp(key, iter->content, ft_strlen(key)) == 0)
		{
			content = ft_strdup(&iter->content[ft_strlen(key)]);
			break ;
		}
		iter = iter->next;
	}
	return (content);
}

char	*cut_front(int start, char *content)
{
	int		i;
	char	*tmp1;

	i = 0;
	while (i < start)
		i++;
	tmp1 = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (i < start)
	{
		tmp1[i] = content[i];
		i++;
	}
	tmp1[i] = '\0';
	return (tmp1);
}

char	*cut_back(int start, int size, char *content)
{
	int		i;
	int		j;
	char	*tmp2;

	i = start + size;
	while (content[i])
	{
		i++;
	}
	tmp2 = (char *)malloc(sizeof(char) * i + 1);
	j = 0;
	i = start + size;
	while (content[i])
	{
		tmp2[j] = content[i];
		j++;
		i++;
	}
	tmp2[j] = '\0';
	return (tmp2);
}

char	*make_check(char *front, char *back, char *change)
{
	int		i;
	int		j;
	int		size;
	char	*check;

	size = ft_strlen(front) + ft_strlen(back) + ft_strlen(change);
	check = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	j = 0;
	while (front[j++])
		check[i++] = 'T';
	j = 0;
	while (change[j++])
		check[i++] = 'F';
	j = 0;
	while (back[j++])
		check[i++] = 'T';
	check[i] = '\0';
	return (check);
}

void	split_change(char	*front, char *change, char *back, t_node **node, t_list	*list)
{
	int		i;
	char	**new;
	t_list	*new_list;
	t_node	*iter;

	iter = *node;
	new_list = init_new_list();
	// change의 맨 첫글자와 마지막 글자가 스페이스면 front, back이랑 합치지 말고 바로 노드
	new = ft_split(change, ' ');
	i = 0;
	//
	t_flag flag;
	flag.quo = 0;
	flag.env = (*node)->env;
	flag.env_with_quo = (*node)->env_with_quo;
	//
	while (new[i])
	{
		if (i == 0)
		{
			make_head_node(ft_strjoin(front, new[i]), flag, new_list);
			new_list->tail->check = make_check(front, "\0", new[i]);
		}
		else if (!new[i + 1])  // 마지막 노드
		{
			join_node(ft_strjoin(new[i], back), flag, new_list);
			new_list->tail->check = make_check("\0", back, new[i]);
		}
		else
		{
			join_node(new[i], flag, new_list);
			new_list->tail->check = make_check("\0", "\0", new[i]);
		}
		new_list->tail->type = 0;
		i++;
	}
////////////////////////////////////////////
	if (iter->prev != NULL)
	{
		iter->prev->next = new_list->head;
		new_list->head->prev = iter->prev;
	}
	else
	{
		new_list->tail->next = iter->next;
		list->head = new_list->head;
	}
	if (iter->next != NULL)
	{
		new_list->tail->next = iter->next;
		iter->next->prev = new_list->tail;
	}
	*node = new_list->head;
////////////////////////////////////////////
}

int	change_to_envp(int start, int size, t_list *envp, t_node **node, int flag, t_list *list)
{
	char	*front;
	char	*back;
	char	*change;
	char	*new;

	front = cut_front(start, (*node)->content);
	back = cut_back(start, size, (*node)->content);
	change = get_env(ft_substr((*node)->content, start + 1, size - 1), envp);
	if (change && flag == 1 && have_space(change))
	{
		if ((*node)->prev != NULL
			&& ((*node)->prev->type == REDIR_IN
				|| (*node)->prev->type == REDIR_OUT
				|| (*node)->prev->type == HEREDOC_OUT))
		{
			// printf("bash: %s: ambiguous redirect\n", tmp);
			stat = 1;
			exit(1);
		}
		split_change(front, change, back, node, list);
		return (1);
	}
	else if (change)  // 빈칸 없으면 그냥 하나로 합쳐서 한 노드에 넣어주기
	{
		new = ft_strjoin(front, change);
		new = ft_strjoin(new, back);
	}
	else
		new = ft_strjoin(front, back);
	(*node)->content = new;
	(*node)->check = make_check(front, back, change);
	return (0);
}
