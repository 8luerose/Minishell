/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:37 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/12 20:13:59 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <readline/readline.h>   // readline을 위한 헤더
# include <readline/history.h>    // add_history를 위한 헤더
# include "libft/libft.h"

# define DOUBLE_Q 1
# define SINGLE_Q 2

enum	e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC_IN,
	HEREDOC_OUT
};

typedef struct s_node
{
	char			*content;
	int				env;
	int				env_with_quo;
	enum e_type		type;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
}	t_list;

typedef struct s_flag
{
	int	quo;
	int	env;
	int	env_with_quo;
}	t_flag;

/////////////////////////////////

// typedef struct s_cmd
// {
// 	char	**cmd_line;
// }	t_cmd;

typedef struct s_redir
{
	char			*redir;
	char			*file_name;
	struct s_redir	*next;
}	t_redir;

typedef struct s_data
{
	char		**cmd_line;
	t_redir			*redir;
	struct s_data	*next;
}	t_data;

/////////////////////////////////

// token
int		is_meta(char c);
void	get_token(char *input, t_list *list);
// make_node
t_node	*ft_lstnew(char *content, t_flag flag);
void	make_head_node(char *content, t_flag flag, t_list *list);
void	join_node(char *content, t_flag flag, t_list *list);
void	make_node(char *content, t_flag flag, t_list *list);
t_data	*init_new_data(void);
t_redir	*init_new_redir(t_node *p);
// expand.c
void	expand_with_quo(t_list	*envp, t_node	*node);
void	expand(t_list	*envp, t_list *list);
// expand2.c
int		check_envp(char	*content);
char	*get_env(char *key, t_list *envp);
char	*cut_front(int start, char *content);
char	*cut_back(int start, int size, char *content);
char	*change_to_envp(int start, int size, char *content, t_list *envp);
// utils
char	*ft_strjoin_c(char const *s1, char c);
char	*ft_strndup(const char *s1, int n);
int		ft_strcmp(const char *s1, const char *s2);
// syntax_error
void	check_syntax_error(t_list *list);
// ft_export
char	*get_key(char	*str);
void	ft_export(t_list *my_envp, char	**cmd_line);
// ft_env
void	ft_env(t_list	*my_envp);
//get_type
void	get_type(t_list	*list);
//get_list(second parsing)
void	get_list(t_list *list, t_data **pipeline_list);
void 	append_cmd(t_data *data, char *word);
void 	append_redir(t_data *data, t_node *current);
//free
void	free_pipeline(t_data *pipeline);
void	free_redirs(t_redir *redir);
void	free_cmd_line(char **cmd_line);
//print
void	print_result(t_data *data);
void	print_result_test(t_data *data);
void	print_type(t_list *list);
//signal
void	set_terminal_print_off(void);
void	set_terminal_print_on(void);
void	handler_sigint(int key);
void	handler_sigquit(int key);

#endif