/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:51:22 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/09 21:07:11 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**copy_envp(char **ev)
// {
// 	int		i;
// 	int		j;
// 	int		size;
// 	char	**my_envp;

// 	size = 0;
// 	while (ev[size])
// 		size++;
// 	my_envp = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (!my_envp)
// 		exit(1);
// 	i = 0;
// 	while (ev[i])
// 	{
// 		size = 0;
// 		while (ev[i][size])
// 			size++;
// 		my_envp[i] = (char *)malloc(sizeof(char) * (size + 1));
// 		if (!my_envp)
// 			exit(1);
// 		j = 0;
// 		while (ev[i][j])
// 		{
// 			my_envp[i][j] = ev[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (my_envp);
// }

char	*make_content(char	*line)
{
	int		i;
	int		size;
	char	*content;

	size = 0;
	while (line[size])
		size++;
	content = (char *)malloc(sizeof(char) * size + 1);
	if (!content)
		exit(1);
	i = 0;
	while (line[i])
	{
		content[i] = line[i];
		i++;
	}
	return (content);
}

void	copy_envp(char	**ev, t_list	*my_envp)
{
	int		i;
	t_flag	flag;
	char	*content;

	i = 0;
	while (ev[i])
	{
		flag.env = 0;
		flag.env_with_quo = 0;
		content = make_content(ev[i]);
		make_node(content, flag, my_envp);
		i++;
	}
}

// void	minishell(char *input, t_list	*my_envp)
void	minishell(char *input)
{
	t_list	*list;
	t_data	*pipeline_list;

	list = (t_list *)malloc(sizeof(t_list));
	list->head = NULL;
	list->tail = NULL;
	get_token(input, list);
	get_type(list);
	// check_syntax_error(list);  // syntax 에러
	// expand(my_envp, list);
	pipeline_list = NULL;
	get_list(list, &pipeline_list);


	t_node *s;
	s = list->head;
	while (s)
	{
		printf("%s            type: %d\n", s->content, s->type);
		s = s->next;
	}

	t_data	*p_data;
	t_redir	*p_redir;
	// char	*p_file_name;
	char	**p_cmd_line;
	int		i;

	p_data = pipeline_list;
	while (p_data)
	{
		p_cmd_line = p_data->cmd_line;
		i = 0;
		while (p_cmd_line)
		{
			printf("cmd_line[%i] = %s\n", i, p_cmd_line[i]);
			i++;
		}

		p_redir = p_data->redir;
		while (p_redir)
		{
			printf("reidr: %s  file_name: %s\n", p_redir->redir, p_redir->file_name);
			p_redir = p_redir->next;
		}
		p_data = p_data->next;
	}


	// gcc -lreadline *.c libft.a -g -fsanitize=address 이걸로 컴파일 해!


	// printf("_____2 \n\n\n");
	// t_data *result;
	// char *test_cmd;
	// result = pipeline_list;

	// while (result)
	// {
	// 	test_cmd = result->cmd_line;
	// 	while (test_cmd)
	// 	{
	// 		printf("%s\n", test_cmd);
	// 		test_cmd++;
	// 	}
	// 	printf("%s\n", result->redir->redir);
	// 	printf("%s\n", result->content);
	// 	result = result->next;
	// }
}

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_list	*my_envp;

	ac = 0;
	av = 0;
	my_envp = (t_list *)malloc(sizeof(t_list));
	my_envp->head = NULL;
	my_envp->tail = NULL;
	copy_envp(ev, my_envp);
	while (1)
	{
		input = readline("💭 : ");
		if (input)
		{
			// minishell(input, my_envp);
			minishell(input);
			add_history(input);
		}
	}
	free(input);
	return (0);
}
