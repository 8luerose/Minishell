/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:37 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/17 15:05:41 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

int	g_stat;

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
	enum e_type		type;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
}	t_list;

typedef struct s_redir
{
	char			*redir;
	char			*file_name;
	char			*limiter;
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
	char	**path;
	t_list	*envp;
}	t_envp;

//bitmap
void		print_bitmap(void);
//close
void		close_prev(t_pipe *fd);
void		close_cur(t_pipe *fd);
void		close_n_wait(t_pipe *fd, int size);
//error
int			cnt_str(char *str);
int			quo_error(void);
int			file_error(char *file_name);
void		command_error(char	*cmd, char *access_path);
//execute_main
void		set_env_pipe(t_envp *my_envp, t_pipe *exec, int size);
void		exec_close_backup(int i, t_pipe *exec);
void		run(t_data *cmd, int size, t_envp *my_envp);
int			builtins_check(t_data *cmd, t_envp *my_envp);
int			execute(t_data *cmd, t_envp *my_envp);
//execute_utils
int			exec_error_check(t_data *cmd);
void		exec_backup(t_pipe *fd, int i);
int			check_ambiguous(char *file_name, t_redir *iter);
//execute_run
char		**get_envp_path(char **ev);
void		get_ev(t_envp	*my_envp);
int			set_io_fd_open(t_redir *iter);
int			set_io_fd(t_data *cmd);
void		exec_cmd(int i, t_data *iter, t_pipe *exec, t_envp *my_envp);
//expand1
int			check_envp_size(char *content);
char		*make_key(char *content, int start, int size);
int			key_is_error_stat(char	*key);
char		*get_env(char *key, t_list *envp);
//expand2
void		free_expand(char *expand);
void		end_space(char cont, t_node **iter, char **new_con, char *expand);
int			start_quo(char	*quo, char tmp_content);
int			end_quo(char *quo, char tmp_content);
int			can_expand(int *size, t_node *iter, char quo, char *tmp_content);
//expand3
void		append_and_increment(char **new_content, char *content, int *i);
void		join_content(char **new_content, char *content, int *i, char quo);
char		*get_expand(int i, int size, char *tmp_content, t_list *envp);
int			unsplitable(char quo, t_node **iter);
int			splitable(char quo, char *expand, int *i, int size);
//expand4
char		*split_expand(char *expand, char **front, t_node **node);
void		join_expand(char **new_content, char *expand, int *i, int size);
void		ch_iter(char **new, char *tmp_content, t_node **iter, t_list *envp);
void		expand_and_delete_quo(t_list *envp, t_list *list);
//free
void		free_pipeline(t_data *data);
void		free_cmd_line(char **cmd_line);
void		free_redirs(t_redir *redir);
void		free_list(t_data	*pipe_parsing);
void		free_token(t_list	*list);
void		free_all(char	**str);
void		free_ev(t_envp	*my_envp);
//ft_cd_utils
void		cd_home_error(void);
void		parent_dir_error(void);
void		cd_error(char	**cmd_line);
//ft_cd
int			check_parent_dir(void);
void		change_pwd_in_env(t_list *my_envp);
void		go_to_home_dir(t_list *my_envp);
void		ft_cd(t_list *my_envp, char **cmd_line);
//ft_echo
int			find_n(char *str);
void		ft_echo(int fd, char **cmd_line);
//ft_env
void		ft_env(int fd, t_list	*my_envp);
//ft_exit_utils
int			check_ll_range(long long n, int minus, char *c);
void		numeric_error(char	*str);
//ft_exit
long long	parse_num(char *str, int *minus, long long *i);
int			ft_atouc(char *str);
int			is_valid_exit_arg(char *arg);
int			ft_exit(char **cmd_line);
//ft_export1
void		export_error(char *cmd);
int			key_check(char	*cmd);
void		export_with_equal(t_list *my_envp, char *cmd_line);
void		export_without_equal(char *cmd_line);
void		ft_export(t_list *my_envp, char **cmd_line, int fd);
//ft_export2
char		*get_key(char	*str);
char		*get_value(char	*str);
int			only_space(char *value);
void		free_replace_content(t_node *node, char *key, char *value);
void		add_to_tail(t_list *my_envp, char *key, char *value);
//ft_pwd
void		ft_pwd(int fd);
//ft_unset
void		delete_node(t_list *my_envp, t_node *iter);
void		unset_node(t_list *my_envp, char *key);
void		ft_unset(t_list	*my_envp, char **cmd_line);
//get_list
t_node		*process_word(t_node *p, t_data *new_data);
t_node		*process_redir(t_node *p, t_data *new_data);
void		connect_new_data(t_data **pipe_data, t_data *new_data);
void		get_list(t_list *list, t_data **pipeline_list);
void		append_cmd(t_data *new_data, char *word);
void		append_redir(t_data *new_data, t_node *p);
//heredoc_utils
int			is_limiter(char *str, char *limiter);
int			is_heredoc_process(t_data	*cmd);
char		*set_file_name(void);
void		set_heredoc_tmp_file(t_data *cmd);
//heredoc
void		read_heredoc(char	*limiter, char	*tmp_file);
void		fork_and_read_heredoc(t_data *cmd, int *status);
int			here_doc(t_data *cmd);
//init
t_data		*init_new_data(void);
t_redir		*init_new_redir(t_node *p);
t_envp		*init_new_envp(void);
t_list		*init_new_list(void);
//is_builtin
int			is_builtin(t_data *cmd);
void		run_builtin(int check, t_data *cmd, t_list *my_envp);
//libft_plus
char		*ft_strjoin_c(char const *s1, char c);
char		*ft_strndup(const char *s1, int n);
int			ft_strcmp(const char *s1, const char *s2);
//main_utils
char		*make_content(char	*line);
void		copy_envp(char	**ev, t_envp	*my_envp);
//main
void		minishell(char *input, t_envp *my_envp);
int			main(int ac, char **av, char **ev);
//make_node
t_node		*ft_lstnew(char *content);
void		make_head_node(char *content, t_list *list);
void		join_node(char *content, t_list *list);
void		make_node(char *content, t_list *list);
void		add_mid(char *content, t_node **iter);
//pipe_utils1
void		set_ev(t_envp	*my_envp);
int			make_path(char **access_path, char **path, char *cmd);
char		*check_is_access(char	*cmd, char **path);
void		unlink_tmp_file(t_data	*cmd);
void		unlink_tmp_file_all(t_data	*cmd);
//pipe_utils2
void		do_cmd_error(t_data *cmd, char **path);
void		do_cmd_builtin(t_data *cmd, t_envp *my_envp);
void		do_cmd_exec(t_data *cmd, t_envp *my_envp, char *access_path);
void		do_cmd(t_data *cmd, t_envp *my_envp, char **path);
//pipe
void		first_pipe(t_data *cmd, t_pipe *exec, t_envp *my_envp, char **path);
void		mid_pipe(t_data *cmd, t_pipe *fd, t_envp *my_envp, char **path);
void		last_pipe(t_data *cmd, t_pipe *fd, t_envp *my_envp, char **path);
//signal
void		set_terminal_print_off(void);
void		handler_sigint(int key);
void		handler_sigterm(void);
void		handler_sig_child(int key);
//syntax_error
int			syntax_exit(void);
int			syntax_errors(t_node *p, t_list *list);
int			check_syntax_error(t_list *list);
//token_utils
int			is_escape(char *input, int i, char quo);
int			is_meta(char c);
int			last_check_quo(char quo);
void		check_quo(char input, char *quo);
void		check_meta_and_quo(char *input, int *i, char *quo, int *size);
//token
void		make_token(t_list *list, char *input, int start, int size);
int			get_token(char *input, t_list *list);
void		not_meta_case(char *input, int *i, char *quo, int *size);
void		meta_quo_case(char *input, int *i, char *quo, int *size);
void		handle_meta_token(t_list *list, char *input, int *i, int *size);
//type
enum e_type	token_type(char	*content);
void		get_type(t_list	*list);

#endif