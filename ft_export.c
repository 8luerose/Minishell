/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:40 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/06 17:17:09 by taehkwon         ###   ########.fr       */
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
		{
			if (str[i - 1] == '-')
				return (0);
			break ;
		}
		i++;
	}
	i++;
	if (i == 1)
		exit(1);
	// key = (char *)malloc(sizeof(char) * (i + 1));
	key = ft_strndup(str, i);
	key = ft_strjoin(key, "=");
	return (key);
}

char	*get_value(char	*str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	i++;
	value = ft_strdup(&str[i]);
	return (value);
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

int	only_space(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] != ' ' && value[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	free_replace_content(t_node *node, char *key, char *value)
{
	free(node->content);
	if (only_space(value))
		node->content = ft_strdup(key);
	else
		node->content = ft_strjoin(key, value);
}

void	add_to_tail(t_list *my_envp, char *key, char *value)
{
	char	*new_content;
	t_node	*new_node;

	if (only_space(value))
		new_content = ft_strdup(key);
	else
		new_content = ft_strjoin(key, value);
	new_node = ft_lstnew(new_content);
	my_envp->tail->next = new_node;
	new_node->prev = my_envp->tail;
	my_envp->tail = new_node;
}

void	export_error(char *cmd)
{
	char	*str;
	char	*str2;
	char	*tmp;

	str = "export: '";
	str2 = "': not a valid identifier";
	tmp = str;
	str = ft_strjoin(tmp, cmd);
	tmp = str;
	str = ft_strjoin(tmp, str2);
	ft_putendl_fd(str, 2);
	g_stat = 1;
}

int	check(char	*cmd)
{
	int	size;

	size = 0;
	while (cmd[size])
		size++;
	if (cmd[size - 1] == '-')
		return (1);
	return (0);
}

void	ft_export(t_list *my_envp, char	**cmd_line, int fd)
{
	int		i;
	char	*key;
	char	*value;
	t_node	*iter;

	if (cmd_line[1] == NULL)
		ft_env(fd, my_envp);
	else if (ft_isdigit(cmd_line[1][0]))
		export_error(cmd_line[1]);
	else
	{
		i = 1;
		while (cmd_line[i])
		{
			if (cmd_line[i][0] == '=')
				export_error(cmd_line[i]);
			else if (ft_strchr(cmd_line[i], '='))
			{
				key = get_key(cmd_line[i]);
				value = get_value(cmd_line[i]);
				if (key == 0)
				{
					export_error(cmd_line[i]);
					return ;
				}
				iter = my_envp->head;
				while (iter && ft_strncmp(key, iter->content, ft_strlen(key)))
					iter = iter->next;
				if (iter)
					free_replace_content(iter, key, value);
				else
					add_to_tail(my_envp, key, value);
			}
			else  // =이 없음
			{
				if (check(cmd_line[i]))
					export_error(cmd_line[i]);
			}
			i++;
		}
	}
}
