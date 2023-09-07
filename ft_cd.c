/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:16:01 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/07 20:00:36 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(char	**cmd_line)
{
	char	*tmp;
	char	*error;

	error = "cd: ";
	tmp = error;
	error = ft_strjoin(tmp, cmd_line[1]);
	perror(error);
	g_stat = 1;
}

int	check_parent_dir(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	return (0);
}

void	change_pwd_in_env(t_list *my_envp)
{
	char	*key;
	t_node	*iter;

	key = "PWD=";
	iter = my_envp->head;
	while (iter)
	{
		if (ft_strncmp(key, iter->content, ft_strlen(key)) == 0)
		{
			free(iter->content);
			iter->content = ft_strjoin(key, getcwd(NULL, 0));
			break ;
		}
		iter = iter->next;
	}
}

//원본 코드 
// void	ft_cd(t_list *my_envp, char **cmd_line)
// {
// 	int		ret;
// 	char	*path;

// 	if (cmd_line[1])
// 		path = ft_strdup(cmd_line[1]);
// 	ret = chdir(path);
// 	if (!cmd_line[1])
// 	{
// 		if (chdir(get_env("HOME", my_envp)))
// 			cd_home_error();
// 	}
// 	else if (ret < 0)
// 	{
// 		if (ft_strlen(get_env("HOME", my_envp)) == 0)
// 			cd_home_error();
// 		else
// 			cd_error(cmd_line);
// 	}
// 	else
// 	{
// 		if (check_parent_dir())
// 		{
// 			parent_dir_error();
// 			chdir(get_env("HOME", my_envp));
// 		}
// 	}
// 	change_pwd_in_env(my_envp);
// }

void	go_to_home_dir(t_list *my_envp)
{
	parent_dir_error();
	chdir(get_env("HOME", my_envp));
}

void	ft_cd(t_list *my_envp, char **cmd_line)
{
	int		ret;
	char	*path;

	if (cmd_line[1])
		path = ft_strdup(cmd_line[1]);
	ret = chdir(path);
	if (!cmd_line[1])
	{
		if (chdir(get_env("HOME", my_envp)))
			cd_home_error();
	}
	else if (ret < 0)
	{
		if (ft_strlen(get_env("HOME", my_envp)) == 0)
			cd_home_error();
		else
			cd_error(cmd_line);
	}
	else
	{
		if (check_parent_dir())
			go_to_home_dir(my_envp);
	}
	change_pwd_in_env(my_envp);
}
