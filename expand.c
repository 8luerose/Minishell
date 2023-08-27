/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:53:16 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/27 20:39:23 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		// printf("stat: %d\n", stat);
		return (ft_itoa(stat));
	}
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

t_node	*expand_just_envp(char *expand, char *front, t_node	**node, t_list *list)
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
			if (ft_strlen(front) != 0 && expand[0] == ' ')
			{
				make_head_node(front, new_list);
				join_node(change[i], new_list);
			}
			else
				make_head_node(ft_strjoin(front, change[i]), new_list);
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
	return (new_list->tail);
}

void	expand(t_list	*envp, t_list	*list)
{
	int		i;
	int		size;
	char	quo;
	char	*key;
	char	*new_content;
	char	*tmp_content;
	t_node	*iter;

	iter = list->head;
	while (iter)
	{
		i = 0;
		new_content = ft_strdup("");
		// iter->content[i]를 tmp_content에 저장해두기 (여기는 값이 바뀌면 안돼)
		tmp_content = ft_strdup(iter->content);
		while (tmp_content[i])
		{
			if (quo == 0
				&& (tmp_content[i] == '\'' || tmp_content[i] == '\"' ))
			{
				quo = tmp_content[i];
				i++;
			}
			else if (tmp_content[i] == quo)
			{
				quo = 0;
				i++;
			}
			else if (tmp_content[i] == '$')
			{
				if (iter->prev && iter->prev->type == HEREDOC_IN)
				{
					new_content = ft_strjoin_c(new_content, tmp_content[i]);
					i++;
				}
				else
				{
					size = check_envp_size(tmp_content, i);
					if (size > 0)  // 치환할게 있다는 뜻
					{
						key = make_key(tmp_content, i + 1, size - 1);
						if (quo == '\'')  // 치환 X
						{
							new_content = ft_strjoin_c(new_content, tmp_content[i]);
							i++;
						}
						else if (quo == '\"' || (quo == 0 && iter->prev && iter->prev->type == REDIR_IN))  // 치환하는데 노드를 안 나누는 경우
						{
							// new_content에 치환한 값을 join
							new_content = ft_strjoin(new_content, get_env(key, envp));
							i += size;
						}
						else if (quo == 0)  // 치환하는데 빈칸 만나면 노드 나누기
						{
							if(ft_strlen(get_env(key, envp)) != 0)
							{
								iter = expand_just_envp(get_env(key, envp), new_content, &iter, list);
								new_content = iter->content;
							}
							i += size;
							char	*expand;
							int		j;
							
							expand = get_env(key, envp);
							j = 0;
							while (expand[j])
								j++;
							if (expand[j - 1] == ' ' && tmp_content[i])
							{
								t_node	*new;

								new = (t_node *)malloc(sizeof(t_node));
								new->type = WORD;
								// new->next = iter->next;
								// iter->next->prev = new;
								// new->prev = iter;
								// iter->next = new;
								if (iter->next != NULL)
								{
									new->next = iter->next;
									iter->next->prev = new;
								}
								else
									new->next = NULL;
								new->prev = iter;
								iter->next = new;
								new_content = ft_strdup("");
								iter = new;
							}
						}
					}
					else
					{
						// new_content에 join
						new_content = ft_strjoin_c(new_content, tmp_content[i]);
						i++;
					}
				}
			}
			else
			{
				// new_content에 join
				new_content = ft_strjoin_c(new_content, tmp_content[i]);
				i++;
			}
		}
		// free(iter->content);
		free(tmp_content);
		iter->content = new_content;
		iter = iter->next;
	}
}
