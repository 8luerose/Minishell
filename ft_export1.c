/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:40 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/10 07:05:21 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	export_with_equal(t_list *my_envp, char *cmd_line)
{
	char	*key;
	char	*value;
	t_node	*iter;

	if (cmd_line[0] == '=')
		export_error(cmd_line);
	else if (ft_strchr(cmd_line, '='))
	{
		key = get_key(cmd_line);
		value = get_value(cmd_line);
		if (!key)
		{
			export_error(cmd_line);
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
}

void	export_without_equal(char *cmd_line)
{
	if (check(cmd_line))
		export_error(cmd_line);
}

void	ft_export(t_list *my_envp, char **cmd_line, int fd)
{
	int	i;

	if (cmd_line[1] == NULL)
		ft_env(fd, my_envp);
	else if (ft_isdigit(cmd_line[1][0]))
		export_error(cmd_line[1]);
	else
	{
		i = 1;
		while (cmd_line[i])
		{
			if (ft_strchr(cmd_line[i], '='))
				export_with_equal(my_envp, cmd_line[i]);
			else
				export_without_equal(cmd_line[i]);
			i++;
		}
	}
}
