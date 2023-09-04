/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:53:16 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/04 20:23:25 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	expand(t_list	*envp, t_list	*list)    // 원본 코코드
// {
// 	int		i;
// 	int		size;
// 	char	quo;
// 	char	*key;
// 	char	*new_content;
// 	char	*tmp_content;
// 	t_node	*iter;

// 	iter = list->head;
// 	while (iter)
// 	{
// 		i = 0;
// 		new_content = ft_strdup("");
// 		// iter->content[i]를 tmp_content에 저장해두기 (여기는 값이 바뀌면 안돼)
// 		tmp_content = ft_strdup(iter->content);
// 		while (tmp_content[i])
// 		{
// 			if (quo == 0
// 				&& (tmp_content[i] == '\'' || tmp_content[i] == '\"' ))
// 			{
// 				quo = tmp_content[i];
// 				i++;
// 			}
// 			else if (tmp_content[i] == quo)
// 			{
// 				quo = 0;
// 				i++;
// 			}
// 			else if (tmp_content[i] == '$')
// 			{
// 				if (iter->prev && iter->prev->type == HEREDOC_IN)
// 				{
// 					new_content = ft_strjoin_c(new_content, tmp_content[i]);
// 					i++;
// 				}
// 				else
// 				{
// 					size = check_envp_size(tmp_content, i);
// 					if (size > 0)  // 치환할게 있다는 뜻
// 					{
// 						key = make_key(tmp_content, i + 1, size - 1);
// 						if (quo == '\'')  // 치환 X
// 						{
// 							new_content = ft_strjoin_c(new_content, tmp_content[i]);
// 							i++;
// 						}
// 						else if (quo == '\"' || (quo == 0 && iter->prev && iter->prev->type == REDIR_IN))  // 치환하는데 노드를 안 나누는 경우
// 						{
// 							// new_content에 치환한 값을 join
// 							new_content = ft_strjoin(new_content, get_env(key, envp));
// 							i += size;
// 						}
// 						else if (quo == 0)  // 치환하는데 빈칸 만나면 노드 나누기
// 						{
// 							if(ft_strlen(get_env(key, envp)) != 0)
// 							{
// 								iter = expand_just_envp(get_env(key, envp), new_content, &iter, list);
// 								new_content = iter->content;
// 							}
// 							i += size;
// 							char	*expand;
// 							int		j;
							
// 							expand = get_env(key, envp);
// 							j = 0;
// 							while (expand[j])
// 								j++;
// 							if (expand[j - 1] == ' ' && tmp_content[i])
// 							{
// 								t_node	*new;

// 								new = (t_node *)malloc(sizeof(t_node));
// 								new->type = WORD;
// 								// new->next = iter->next;
// 								// iter->next->prev = new;
// 								// new->prev = iter;
// 								// iter->next = new;
// 								if (iter->next != NULL)
// 								{
// 									new->next = iter->next;
// 									iter->next->prev = new;
// 								}
// 								else
// 									new->next = NULL;
// 								new->prev = iter;
// 								iter->next = new;
// 								new_content = ft_strdup("");
// 								iter = new;
// 							}
// 						}
// 					}
// 					else
// 					{
// 						// new_content에 join
// 						new_content = ft_strjoin_c(new_content, tmp_content[i]);
// 						i++;
// 					}
// 				}
// 			}
// 			else
// 			{
// 				// new_content에 join
// 				new_content = ft_strjoin_c(new_content, tmp_content[i]);
// 				i++;
// 			}
// 		}
// 		// free(iter->content);
// 		free(tmp_content);
// 		iter->content = new_content;
// 		iter = iter->next;
// 	}
// }

int	check_envp_size(char	*content, int start_idx)
{
	int	i;
	int	size;

	i = start_idx;
	if (content[i + 1] && content[i + 1] == '?')
		return (2);
	if ((content[i + 1] >= 'a' && content[i + 1] <= 'z')
		|| (content[i + 1] >= 'A' && content[i + 1] <= 'Z')
		|| (content[i + 1] >= '0' && content[i + 1] <= '9')
		|| content[i + 1] == '_')
		i++;
	else
		return (-1);
	size = 1;
	while (content[i])
	{
		if (!((content[i] >= 'a' && content[i] <= 'z')
				|| (content[i] >= 'A' && content[i] <= 'Z')
				|| (content[i] >= '0' && content[i] <= '9')
				|| content[i] == '_'))
			break ;
		{
			i++;
			size++;
		}
	}
	return (size);
}

char	*make_key(char *content, int start, int size)
{
	char	*key;

	key = ft_substr(content, start, size);
	return (key);
}

int	key_is_error_stat(char	*key)
{
	if (ft_strcmp(key, "?") == 0)
		return (1);
	return (0);
}

char	*get_env(char *key, t_list *envp)
{
	char	*content;
	t_node	*iter;

	if (key_is_error_stat(key))
		return (ft_itoa(stat));
	content = "\0";
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

char	*split_expand(char *expand, char **front, t_node	**node, t_list *list)
{
	// 치환할 부분을 빈칸 기준으로 split -> 첫번째 인자를 new_content에 조인,
	// 두번째 부터는 새로 노드 생성,
	// 마지막 인자는 content[i]이 뒤에 남아있는 문자열과 합치기
	int		i;
	char	**change;
	t_list	*new_list;
	t_node	*iter;

	new_list = init_new_list();
	change = ft_split(expand, ' ');
	i = 0;
	while (change[i])
	{
		if (i == 0)
		{
			if (ft_strlen((*front)) != 0 && expand[0] == ' ')
			{
				make_head_node((*front), new_list);
				join_node(change[i], new_list);
			}
			else
				make_head_node(ft_strjoin((*front), change[i]), new_list);
		}
		else
			join_node(change[i], new_list);
		i++;
	}
	iter = *node;
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
	*node = new_list->tail;
	(*front) = (*node)->content;
	return ((*front));
}

void	free_expand(char *expand)
{
	if (expand)
		free(expand);
}

void	expand_end_with_space(char	tmp_content, t_node	**iter, char	**new_content, char	*expand)
{
	t_node	*new;
	int		j;

	j = 0;
	while (expand[j])
		j++;
	if (expand[j - 1] == ' ' && tmp_content)
	{
		new = (t_node *)malloc(sizeof(t_node));
		new->type = WORD;
		if ((*iter)->next != NULL)
		{
			new->next = (*iter)->next;
			(*iter)->next->prev = new;
		}
		else
			new->next = NULL;
		new->prev = (*iter);
		(*iter)->next = new;
		(*new_content) = ft_strdup("");
		(*iter) = new;
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

int	end_quo(char	*quo, char	tmp_content)
{
	if (tmp_content == (*quo))
	{
		(*quo) = 0;
		return (1);
	}
	return (0);
}

int	can_expand(int *size, t_node	*iter, char quo, char *tmp_content, int i)
{
	(*size) = check_envp_size(tmp_content, i);
	if ((*size) > 0 && quo != '\'')
	{
		if (iter->prev && iter->prev->type == HEREDOC_IN)
			return (0);
		return (1);
	}
	return (0);
}

void	join_with_new_content(char	**new_content, char	*tmp_content, int *i, char quo)
{
	if (tmp_content[*i] == '\\')
	{
		if (quo == 0)  // 이스케이프 문자 제거
		{
			if (tmp_content[(*i) + 1] && (tmp_content[(*i) + 1] == 'n' || tmp_content[(*i) + 1] == '\'' || tmp_content[(*i) + 1] == '\"'))
				(*i)++;
		}
		else if (quo == '\"')
		{
			if (tmp_content[(*i) + 1] && tmp_content[(*i) + 1] == '\"')
				(*i)++;
			else
			{
				(*new_content) = ft_strjoin_c((*new_content), tmp_content[*i]);
				(*i)++;
			}
		}
		else if (quo == '\'')
		{
			(*new_content) = ft_strjoin_c((*new_content), tmp_content[*i]);
			(*i)++;
		}
	}
	(*new_content) = ft_strjoin_c((*new_content), tmp_content[*i]);
	(*i)++;
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

int unsplitable(char quo, t_node	**iter)
{
	if (quo == '\"' || (quo == 0 && (*iter)->prev && (*iter)->prev->type == REDIR_IN))
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

void	join_with_expand(char	**new_content, char	*expand, int *i, int size)
{
	(*new_content) = ft_strjoin((*new_content), expand);
	(*i) += size;
}

void	check_iter_content(char	**new_content, char	*tmp_content, t_node	**iter, t_list	*envp, t_list	*list)
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
		else if (tmp_content[i] == '$' && can_expand(&size, (*iter), quo, tmp_content, i))
		{
			expand = get_expand(i, size, tmp_content, envp);
			if (unsplitable(quo, iter))
				join_with_expand(new_content, expand, &i, size);
			else if (splitable(quo, expand, &i, size))
			{
				(*new_content) = split_expand(expand, new_content, iter, list);
				expand_end_with_space(tmp_content[i], iter, new_content, expand);
			}
		}
		else
			join_with_new_content(new_content, tmp_content, &i, quo);
	}
}

/**
 * tmp_content, new_content, i를 묶어서 구조체로 만들던가
 * expand 관련된 거를 다 묶어 구조체로 만들던가
*/

void	expand_and_delete_quo(t_list	*envp, t_list	*list)
{
	t_node	*iter;
	char	*new_content;
	char	*tmp_content;

	iter = list->head;
	while (iter)
	{
		new_content = ft_strdup("");
		tmp_content = ft_strdup(iter->content);
		check_iter_content(&new_content, tmp_content, &iter, envp, list);
		free(tmp_content);
		iter->content = new_content;   //따옴표가 제거된 content로 갱신
		iter = iter->next;
	}
}
