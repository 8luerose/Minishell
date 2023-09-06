/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:41:12 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/06 17:19:30 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_data *cmd)
{
	char	*cmd_name;

	cmd_name = cmd->cmd_line[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (ECHOO);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (CD);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (ENV);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (EXIT);
	return (NOT_BUILTIN);
}

void	run_builtin(int check, t_data *cmd, t_list *my_envp)
{
	if (check == ECHOO)
		ft_echo(cmd->o_fd, cmd->cmd_line);
	else if (check == CD)
		ft_cd(my_envp, cmd->cmd_line);
	else if (check == PWD)
		ft_pwd(cmd->o_fd);
	else if (check == EXPORT)
		ft_export(my_envp, cmd->cmd_line, cmd->o_fd);
	else if (check == UNSET)
		ft_unset(my_envp, cmd->cmd_line);
	else if (check == ENV)
		ft_env(cmd->o_fd, my_envp);
	else if (check == EXIT)
		ft_exit(cmd->cmd_line);
}
