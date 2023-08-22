/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:29:09 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/19 11:26:38 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	have_space(char	*content)
// {
// 	printf("have space : %s\n", content);
// 	int	i;
// 	int	quo;
// 	int	double_quo;

// 	i = 0;
// 	quo = 1;
// 	double_quo = 1;
// 	while (content[i])
// 	{
// 		if (content[i] == '\'' || content[i] == '\"')
// 			quo *= -1;
// 		if (content[i] == ' ' && quo == 1)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int	have_space(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

// void	make_check2(t_node	*iter, char *check, char *content)
// {
// 	int		i;
// 	int 	start;
// 	int		end;
// 	int		quo;
// 	char	*new_check;

// 	start = 0;
// 	end = 0;
// 	quo = 0;
// 	i = 0;
// 	while (content[i])
// 	{
// 		if (quo == 0 && content[i] == ' ')
// 		{
// 			end = i - 1;
// 			new_check = ft_substr(check, start, end - start + 1);
// 			iter->check = new_check;
// 			iter = iter->next;
// 		}
// 		while (quo == 0 && content[i] == ' ')
// 			i++;
// 		if (i != 0 && quo == 0 && content [i - 1] == ' ' && content[i] != ' ')
// 			start = i;
// 		if (quo == 0 && content[i] == '\'')
// 			quo = 1;
// 		else if (quo == 1 && content[i] == '\'')
// 			quo = 0;
// 		i++;
// 		// if (!content[i])
// 		// {
// 		// }
// 		// i++;
// 	}
// 	end = i - 1;
// 	new_check = ft_substr(check, start, end - start + 1);
// 	// if (iter)
// 		iter->check = new_check;
// 	// iter = iter->next;
// }

// void	split_node(t_node **node, t_list *list, char *check)
// {
// 	t_list	*new_list;
// 	t_node	*iter;

// 	new_list = (t_list *)malloc(sizeof(t_list));
// 	new_list->head = NULL;
// 	new_list->tail = NULL;
// 	iter = *node;
// 	get_token(iter->content, new_list);
// 	get_type(new_list);
// 	if (iter->prev != NULL)
// 	{
// 		iter->prev->next = new_list->head;
// 		new_list->head->prev = iter->prev;
// 	}
// 	else
// 	{
// 		new_list->tail->next = iter->next;
// 		list->head = new_list->head;
// 	}
// 	if (iter->next != NULL)
// 	{
// 		new_list->tail->next = iter->next;
// 		iter->next->prev = new_list->tail;
// 	}
// 	*node = new_list->head;
// 	make_check2(new_list->head, check, iter->content);
// 	free(iter->content);
// 	free(iter);
// 	check = NULL;
// }

void	expand_just_envp(t_list	*envp, t_node	**node, t_list *list)
{
	int		i;
	int		quo;
	int		size;
	char	*content;

	quo = 0;
	size = 0;
	content = (*node)->content;
	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			size = check_envp(&content[i]);
			if (size > 0)
			{
				if (change_to_envp(i, size, envp, node, 1, list))
					break ;
			}
		}
		i++;
	}
}

void	expand_with_quo(t_list	*envp, t_node	**node, t_list *list)
{
	int		i;
	int		quo;
	int		size;
	char	*content;

	quo = 0;
	size = 0;
	i = 0;
	content = (*node)->content;
	while (content[i])
	{
		if (content[i] == '\"' && quo == 0)
			quo = 1;
		else if (content[i] == '\"' && quo == 1)
			quo = 0;
		else if (content[i] == '$' && quo == 1)
		{
			size = check_envp(&content[i]);
			if (size > 0)
				change_to_envp(i, size, envp, node, 0, list);
		}
		i++;
	}
}

void	expand(t_list	*envp, t_list *list)
{
	t_node	*iter;
	// char	*tmp;

	iter = list->head;
	while (iter)
	{
		// << 뒤는 리미터라 확장이 일어나면 X
		if (iter != list->head && iter->prev->type == 4)
		{
			iter = iter -> next;
			continue ;
		}
		if (iter->env == 1)
		{
			// tmp = ft_strdup(iter->content);
			expand_just_envp(envp, &iter, list);
			// if (have_space(iter->content))
			// {
			// 	// <, > 뒤에 $A 가 확장이 일어난 경우 빈칸이 있으면 다음과 같은 오류 출력
			// 	if (iter != list->head
			// 		&& (iter->prev->type == REDIR_IN || iter->prev->type == REDIR_OUT || iter->prev->type == HEREDOC_OUT))
			// 	{
			// 		printf("bash: %s: ambiguous redirect\n", tmp);
			// 		stat = 1;
			// 		exit(1);
			// 	}
			// 	split_node(&iter, list, iter->check);
			// }
		}
		if (iter && iter->env_with_quo == 1)
		{
			expand_with_quo(envp, &iter, list);
		}
		iter = iter->next;
	}
}
