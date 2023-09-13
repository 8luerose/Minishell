/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:40 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/11 17:06:59 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error(char *cmd)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_stat = 1;
}

int	key_check(char	*cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (i == 0 && ft_isdigit(cmd[i]))
			return (1);
		if (!(ft_isalnum(cmd[i]) || cmd[i] == '_'))
			return (1);
		i++;
	}
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
		if (!key)
		{
			export_error(cmd_line);
			return ;
		}
		value = get_value(cmd_line);
		iter = my_envp->head;
		while (iter && ft_strncmp(key, iter->content, ft_strlen(key)))
			iter = iter->next;
		if (iter)
			free_replace_content(iter, key, value);
		else
			add_to_tail(my_envp, key, value);
		free(key);
		free(value);
	}
}

void	export_without_equal(char *cmd_line)
{
	if (key_check(cmd_line))
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
