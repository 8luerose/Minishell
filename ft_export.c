/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:40 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/09 17:11:57 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*make_content(char	*line)
// {
// 	int		i;
// 	int		size;
// 	char	*content;

// 	size = 0;
// 	while (line[size])
// 		size++;
// 	content = (char *)malloc(sizeof(char) * size + 1);
// 	if (!content)
// 		exit(1);
// 	i = 0;
// 	while (line[i])
// 	{
// 		content[i] = line[i];
// 		i++;
// 	}
// 	return (content);
// }

// void	copy_envp(char	**ev, t_list	*my_envp)
// {
// 	int		i;
// 	t_flag	flag;
// 	char	*content;

// 	i = 0;
// 	while (ev[i])
// 	{
// 		flag.env = 0;
// 		flag.env_with_quo = 0;
// 		content = make_content(ev[i]);
// 		make_node(content, flag, my_envp);
// 		i++;
// 	}
// }

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
	key = (char *)malloc(sizeof(char) * (i + 1));
	key = ft_strndup(str, i);
	return (key);
}

void	ft_export(t_list *my_envp, char	**cmd_line)
{
	char	*key;
	t_node	*iter;
	t_node	*new;
	t_flag	flag;

	flag.env = 0;
	flag.env_with_quo = 0;
	flag.quo = 0;  // flag 초기화 하는 함수 만들기

	if (cmd_line[1] == NULL)
		ft_env(my_envp);
	else
	{
		if (ft_strchr(cmd_line[1], '='))
		{
			key = get_key(cmd_line[1]);
			iter = my_envp->head;
			while (iter)
			{
				if (ft_strncmp(key, iter->content, ft_strlen(key)) == 0)
					break ;
				iter = iter->next;
			}
			if (iter)
			{
				free(iter->content);
				iter->content = ft_strdup(cmd_line[1]);
			}
			else
			{
				new = ft_lstnew(cmd_line[1], flag);
				my_envp->tail->next = new;
				new->prev = my_envp->tail;
				my_envp->tail = new;
			}
		}
	}
}

// int main(int ac, char **av, char **ev)
// {
// 	t_list	*my_envp;
// 	char	*arr[3];
	
// 	(void)ac;
// 	(void)av;
// 	my_envp = (t_list *)malloc(sizeof(t_list));
// 	my_envp->head = NULL;
// 	my_envp->tail = NULL;
// 	copy_envp(ev, my_envp);
// 	arr[0] = ft_strdup("export");
// 	arr[1] = ft_strdup("$USER = ");
// 	arr[2] = NULL;
	
// 	ft_export(my_envp, arr);
// 	ft_env(my_envp);
	

// }
