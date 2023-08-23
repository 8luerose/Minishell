/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:40 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/24 04:50:33 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char	*str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	i++;
	if (i == 1)
		exit(1);
	key = (char *)malloc(sizeof(char) * (i + 1));
	key = ft_strndup(str, i);
	key = ft_strjoin(key, "=");
	return (key);
}

// 원본 코드
// void	ft_export(t_list *my_envp, char	**cmd_line, int fd)
// {
// 	int		i;
// 	char	*key;
// 	t_node	*iter;
// 	t_flag	flag;

// 	flag.env = 0;
// 	flag.env_with_quo = 0;
// 	flag.quo = 0;  // flag 초기화 하는 함수 만들기
// 	if (cmd_line[1] == NULL)
// 		ft_env(fd, my_envp);
// 	else
// 	{
// 		i = 1;
// 		while (cmd_line[i])
// 		{
// 			if (cmd_line[i][0] == '=')
// 				printf("bash: export: '%s': not a valid identifier\n", cmd_line[i]);
// 			else if (ft_strchr(cmd_line[i], '='))
// 			{
// 				key = get_key(cmd_line[i]);
// 				iter = my_envp->head;
// 				while (iter)
// 				{
// 					if (ft_strncmp(key, iter->content, ft_strlen(key)) == 0)
// 						break ;
// 					iter = iter->next;
// 				}
// 				if (iter)
// 				{
// 					free(iter->content);
// 					iter->content = ft_strdup(cmd_line[i]);
// 				}
// 				else
// 				{
// 					iter = ft_lstnew(cmd_line[i], flag);
// 					my_envp->tail->next = iter;
// 					iter->prev = my_envp->tail;
// 					my_envp->tail = iter;
// 				}	
// 			}
// 			i++;
// 		}
// 	}
// }

void	free_replace_content(t_node *node, char *new_content)
{
	free(node->content);
	node->content = ft_strdup(new_content);
}

void	add_to_tail(t_list *my_envp, char *data, t_flag flag)
{
	t_node	*new_node;

	new_node = ft_lstnew(data, flag);
	my_envp->tail->next = new_node;
	new_node->prev = my_envp->tail;
	my_envp->tail = new_node;
}

void	ft_export(t_list *my_envp, char	**cmd_line, int fd)
{
	int		i;
	char	*key;
	t_node	*iter;
	t_flag	flag;

	init_flag(&flag);
	if (cmd_line[1] == NULL)
		ft_env(fd, my_envp);
	else
	{
		i = 1;
		while (cmd_line[i])
		{
			if (cmd_line[i][0] == '=')
				printf("bash: export: '%s': not a valid identifier\n", cmd_line[i]);
			else if (ft_strchr(cmd_line[i], '='))
			{
				key = get_key(cmd_line[i]);
				iter = my_envp->head;
				while (iter && ft_strncmp(key, iter->content, ft_strlen(key)))
					iter = iter->next;
				if (iter)
					free_replace_content(iter, cmd_line[i]);
				else
					add_to_tail(my_envp, cmd_line[i], flag);	
			}
			i++;
		}
	}
}
