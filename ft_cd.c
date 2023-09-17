/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:16:01 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/10 21:03:48 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parent_dir(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	free(pwd);
	return (0);
}

void	change_pwd_in_env(t_list *my_envp)
{
	char	*cur;
	char	*key;
	t_node	*iter;

	key = ft_strdup("PWD=");
	iter = my_envp->head;
	while (iter)
	{
		if (ft_strncmp(key, iter->content, ft_strlen(key)) == 0)
		{
			cur = getcwd(NULL, 0);
			if (cur)
			{
				free(iter->content);
				iter->content = ft_strjoin(key, cur);
				free(cur);
			}
			break ;
		}
		iter = iter->next;
	}
	free(key);
}

void	go_to_home_dir(t_list *my_envp)
{
	char	*path;

	parent_dir_error();
	path = get_env(ft_strdup("HOME"), my_envp);
	if (ft_strlen(path) == 0)
		chdir("/");
	else
	{
		chdir(path);
		free(path);
	}
}

void	ft_cd(t_list *my_envp, char **cmd_line)
{
	char	*path;

	path = NULL;
	if (!cmd_line[1])
	{
		path = get_env(ft_strdup("HOME"), my_envp);
		if (ft_strlen(path) == 0)
			cd_home_error();
		else
		{
			chdir(path);
			free(path);
		}
	}
	else
	{
		if (check_parent_dir())
			go_to_home_dir(my_envp);
		else
		{
			if (chdir(cmd_line[1]) < 0)
				cd_error(cmd_line);
		}
	}
	change_pwd_in_env(my_envp);
}
