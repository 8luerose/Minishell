/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:51:22 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/17 15:07:58 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ev(t_envp	*my_envp)
{
	int	i;

	i = 0;
	while (my_envp->ev[i])
	{
		free(my_envp->ev[i]);
		i++;
	}
	free(my_envp->ev);
	if (my_envp->path)
		free_all(my_envp->path);
}

void	minishell(char *input, t_envp *my_envp)
{
	t_list	*list;
	t_data	*pipe_parsing;

	if (!(*input))
		return ;
	list = init_new_list();
	if (get_token(input, list) == 0)
	{
		free_token(list);
		return ;
	}
	get_type(list);
	if (check_syntax_error(list))
	{
		free_token(list);
		return ;
	}
	expand_and_delete_quo(my_envp->envp, list);
	pipe_parsing = NULL;
	get_list(list, &pipe_parsing);
	execute(pipe_parsing, my_envp);
	free_token(list);
	unlink_tmp_file_all(pipe_parsing);
	free_list(pipe_parsing);
}

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_envp	*my_envp;

	g_stat = 0;
	set_terminal_print_off();
	(void)ac;
	(void)av;
	print_bitmap();
	my_envp = init_new_envp();
	copy_envp(ev, my_envp);
	while (1)
	{
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell: ");
		if (input)
		{
			add_history(input);
			minishell(input, my_envp);
		}
		else
			handler_sigterm();
		free(input);
	}
	return (g_stat);
}
