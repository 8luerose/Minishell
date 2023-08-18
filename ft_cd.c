/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:16:01 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/11 17:17:18 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 상위 디렉토리가 삭제 되었을 경우 어떻게 처리 해야하지?

void	cd_error(char	**cmd_line)
{
	char	*error;

	error = "bash: ";
	error = ft_strjoin(error, cmd_line[0]);
	error = ft_strjoin(error, ": ");
	error = ft_strjoin(error, cmd_line[1]);
	perror(error);
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

void	ft_cd(t_list *my_envp, char **cmd_line)
{
	int		ret;
	char	*path;

	path = ft_strdup(cmd_line[1]);
	ret = chdir(path);
	if (ret < 0)
		cd_error(cmd_line);
	change_pwd_in_env(my_envp);
}
