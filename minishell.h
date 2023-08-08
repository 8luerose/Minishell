/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:37 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/08 16:49:26 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
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
// 	t_cmd	*next;
// }	t_cmd;

// typedef struct s_redir
// {
// 	char	*redir;
// 	char	*file_name;
// 	t_redir	*next;
// }	t_redir;

// typedef struct s_data
// {
// 	t_cmd	*cmd;
// 	t_redir	*redir;
// 	t_data	*next;
// }	t_data;

/////////////////////////////////

// token
int		is_meta(char c);
void	get_token(char *input, t_list *list);
// make_node
t_node	*ft_lstnew(char *content, t_flag flag);
void	make_head_node(char *content, t_flag flag, t_list *list);
void	join_node(char *content, t_flag flag, t_list *list);
void	make_node(char *content, t_flag flag, t_list *list);
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

#endif