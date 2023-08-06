/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:37 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 19:40:11 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>   // readline을 위한 헤더
# include <readline/history.h>    // add_history를 위한 헤더

# define DOUBLE_Q 1
# define SINGLE_Q 2

// # define WORD 0
// # define  0

// typedef enum e_type
// {
// 	word,
// }
// enum 작성할 것

typedef struct s_node
{
	char			*content;
	int				env;
	int				env_with_quo;
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

typedef struct s_cmd
{
	char			**cmd_line;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_redir
{
	char			**redir;
	char			*file_name;
	struct s_redir	*next;
}	t_redir;

typedef struct s_data
{
	struct t_cmd	*cmd;
	struct t_redir	*redirect;
	struct t_data	*next;
}	t_data;

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
// utils
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char c);
int		ft_strcmp(const char *s1, const char *s2);
// syntax_error
void	check_syntax_error(t_list *list);
// token_grouping
void 	get_group_token(t_list *list);
// void	group_node_init(t_cmd *cmd, t_redir *redir, t_data *data);

#endif