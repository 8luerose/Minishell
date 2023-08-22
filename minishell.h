/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:37 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/22 17:36:27 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>   // readline을 위한 헤더
# include <readline/history.h>    // add_history를 위한 헤더
# include "libft/libft.h"

# define DOUBLE_Q 1
# define SINGLE_Q 2

int	stat;

enum	e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC_IN,
	HEREDOC_OUT,
	ECHOO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NOT_BUILTIN,
};

typedef struct s_node
{
	char			*content;
	char			*check;
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

typedef struct s_redir
{
	char			*redir;
	char			*file_name;
	struct s_redir	*next;
}	t_redir;

typedef struct s_data
{
	char			**cmd_line;
	int				i_fd;
	int				o_fd;
	t_redir			*redir;
	struct s_data	*next;
}	t_data;

typedef struct s_pipe
{
	int	size;
	int	prev_fd[2];
	int	cur_fd[2];
}	t_pipe;

typedef struct s_envp
{
	char	**ev;
	t_list	*envp;
}	t_envp;

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
t_envp	*init_new_envp(void);
t_list	*init_new_list(void);
// expand.c
void	expand_with_quo(t_list	*envp, t_node	**node, t_list *list);
void	expand(t_list	*envp, t_list *list);
int		have_space(char	*content);
// expand2.c
int		check_envp(char	*content);
char	*get_env(char *key, t_list *envp);
char	*cut_front(int start, char *content);
char	*cut_back(int start, int size, char *content);
int		change_to_envp(int start, int size, t_list *envp, t_node **node, int flag, t_list *list);
// utils
char	*ft_strjoin_c(char const *s1, char c);
char	*ft_strndup(const char *s1, int n);
int		ft_strcmp(const char *s1, const char *s2);
// syntax_error
void	check_syntax_error(t_list *list);
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
// execute
int		set_io_fd(t_data *cmd);
int		execute(t_data	*cmd, t_envp	*my_envp);
// is_builtin
void	run_builtin(int check, t_data *cmd, t_list *my_envp);
int		is_builtin(t_data *cmd);
// built_in
// ft_echo
void	ft_echo(int fd, char **cmd_line);
int		find_n(char *str);
// ft_cd
void	ft_cd(t_list *my_envp, char **cmd_line);
void	change_pwd_in_env(t_list *my_envp);
void	cd_error(char	**cmd_line);
// ft_pwd
void	ft_pwd(int fd);
// ft_export
void	ft_export(t_list *my_envp, char	**cmd_line, int fd);
char	*get_key(char	*str);
// ft_unset
void	ft_unset(t_list *my_envp, char **cmd_line);
// ft_env
void	ft_env(int fd, t_list	*my_envp);
// ft_exit
int		ft_exit(char **cmd_line);
// heredoc
char	*set_file_name(void);
int		is_limiter(char *str, char *limiter);
void	read_heredoc(char	*limiter, int file_fd);
void	heredoc_open(t_data	*cmd);
// pipe
int		check_is_access(char **access_path, char **path, char *cmd);
// void	do_cmd(t_data	*cmd, t_envp *my_envp, char **path);
int		do_cmd(t_data	*cmd, t_envp *my_envp, char **path);
void	first_pipe(t_data *cmd, t_pipe *exec, t_envp *my_envp, char **path);
void	mid_pipe(t_data *cmd, t_pipe *fd, t_envp *my_envp, char **path);
void	last_pipe(t_data *cmd, t_pipe *fd, t_envp *my_envp, char **path);
// close
void	close_prev(t_pipe *fd);
void	close_cur(t_pipe *fd);
void	close_n_wait(t_pipe *fd, int size);
// error
int		cnt_str(char *str);
void	command_error(char *cmd);
int		file_error(char *file_name);
int		system_error(void);
//signal
void	set_terminal_print_off(void);
void	set_terminal_print_on(void);
void	handler_sigint(int key);
void	handler_sig_child(int key);
void	handler_sigterm(void);

#endif