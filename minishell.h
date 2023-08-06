/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:37 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 19:52:36 by seojchoi         ###   ########.fr       */
=======
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:37 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 19:40:11 by taehkwon         ###   ########.fr       */
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>   // readline을 위한 헤더
# include <readline/history.h>    // add_history를 위한 헤더
<<<<<<< HEAD
# include "libft/libft.h"
=======
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed

# define DOUBLE_Q 1
# define SINGLE_Q 2

<<<<<<< HEAD
=======
// # define WORD 0
// # define  0

// typedef enum e_type
// {
// 	word,
// }
// enum 작성할 것

>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
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

<<<<<<< HEAD
=======
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

>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
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
<<<<<<< HEAD
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
=======
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
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed

#endif