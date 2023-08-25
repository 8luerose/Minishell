/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:05 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/25 18:42:35 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
// 원본 코드
void	get_token(char *input, t_list *list)
{
	int		i;
	char	*buf;
	char	*tmp;
	t_flag	flag;

	i = 0;
	flag.quo = 0;
	flag.env = 0;
	flag.env_with_quo = 0;
	buf = ft_strdup("");
	while (input[i])
	{
		if (!is_meta(input[i]))
		{
			if (flag.quo == 0)
			{
				if (input[i] == '\"')
					flag.quo = DOUBLE_Q;
				else if (input[i] == '\'')
					flag.quo = SINGLE_Q;
				else if (input[i] == '$')
					flag.env = 1;
			}
			else
			{
				if (input[i] == '\"' && flag.quo == DOUBLE_Q)
					flag.quo = 0;
				else if (input[i] == '\'' && flag.quo == SINGLE_Q)
					flag.quo = 0;
			}
			if (flag.quo == DOUBLE_Q && input[i] == '$')
				flag.env_with_quo = 1;
			tmp = buf;
			buf = ft_strjoin_c(tmp, input[i]);
			free(tmp);
		}
		else if (is_meta(input[i]) && flag.quo > 0)
		{
			tmp = buf;
			buf = ft_strjoin_c(tmp, input[i]);
			free(tmp);
		}
		else
		{
			if (flag.quo)
				exit(1);
			if (buf[0] != 0)
			{
				make_node(buf, flag, list);
				flag.env = 0;
				flag.env_with_quo = 0;
			}
			if (input[i] != ' ')
			{
				if (input[i + 1]
					&& ((input[i] == '<' && input[i + 1] == '<')
						|| (input[i] == '>' && input[i + 1] == '>')))
				{
					tmp = ft_strndup(&input[i], 2);
					i++;
				}
				else
					tmp = ft_strndup(&input[i], 1);
				buf = ft_strjoin_c(tmp, input[i]);
				free(tmp);
				make_node(buf, flag, list);
			}
			free(buf);
			buf = ft_strdup("");
		}
		i++;
	}
	if (flag.quo)
		exit(1);
	if (buf[0] != 0)
		make_node(buf, flag, list);
	free(buf);
}

// 1차 수정 코드
// static void	update_flags(char c, t_flag *flag)
// {
// 	if (flag->quo == 0)
// 	{
// 		if (c == '\"')
// 			flag->quo = DOUBLE_Q;
// 		else if (c == '\'')
// 			flag->quo = SINGLE_Q;
// 		else if (c == '$')
// 			flag->env = 1;
// 	}
// 	else
// 	{
// 		if (c == '\"' && flag->quo == DOUBLE_Q)
// 			flag->quo = 0;
// 		else if (c == '\'' && flag->quo == SINGLE_Q)
// 			flag->quo = 0;
// 	}
// 	if (flag->quo == DOUBLE_Q && c == '$')
// 		flag->env_with_quo = 1;
// }

// 1차 수정 코드
// static void	handle_meta(char *input, int *i, char **buf, t_flag *flag, t_list *list)
// {
// 	char	*tmp;

// 	if (flag->quo)
// 		exit(1);
// 	if ((*buf)[0] != 0)
// 	{
// 		make_node(*buf, *flag, list);
// 		flag->env = 0;
// 		flag->env_with_quo = 0;
// 	}
// 	if (input[*i] != ' ' && input[*i + 1] && 
// 	   ((input[*i] == '<' && input[*i + 1] == '<') || 
// 	    (input[*i] == '>' && input[*i + 1] == '>')))
// 	{
// 		tmp = ft_strndup(&input[*i], 2);
// 		(*i)++;
// 	}
// 	else
// 		tmp = ft_strndup(&input[*i], 1);
// 	*buf = ft_strjoin_c(tmp, input[*i]);
// 	free(tmp);
// 	make_node(*buf, *flag, list);	
// 	free(*buf);
// 	*buf = ft_strdup("");
// }

// static void append_char_to_buf(char **buf, char c)
// {
//     char *tmp;
	
// 	tmp = *buf;
//     *buf = ft_strjoin_c(tmp, c);
//     free(tmp);
// }

// static void	update_flags_and_buf(char c, t_flag *flag, char **buf)
// {
// 	if (flag->quo == 0)
// 	{
// 		if (c == '\"')
// 			flag->quo = DOUBLE_Q;
// 		else if (c == '\'')
// 			flag->quo = SINGLE_Q;
// 		else if (c == '$')
// 			flag->env = 1;
// 	}
// 	else
// 	{
// 		if (c == '\"' && flag->quo == DOUBLE_Q)
// 			flag->quo = 0;
// 		else if (c == '\'' && flag->quo == SINGLE_Q)
// 			flag->quo = 0;
// 	}
// 	if (flag->quo == DOUBLE_Q && c == '$')
// 		flag->env_with_quo = 1;
// 	append_char_to_buf(buf, c);
// }

// void	get_token(char *input, t_list *list)
// {
// 	int		i;
// 	char	*buf;
// 	t_flag	flag;

// 	i = 0;
// 	init_flag(&flag);  
// 	buf = ft_strdup("");
// 	while (input[i])
// 	{
// 		if (!is_meta(input[i]))
// 			update_flags_and_buf(input[i], &flag, &buf);
// 		else if (is_meta(input[i]) && flag.quo > 0)
// 			append_char_to_buf(&buf, input[i]);
// 		else
// 			handle_meta(input, &i, &buf, &flag, list);
// 		i++;
// 	}
// 	if (flag.quo)
// 		exit(1);
// 	if (buf[0] != 0)
// 		make_node(buf, flag, list);
// 	free(buf);
// }

// 2차 수정코드
// static void add_to_buffer(char **buf, char c)
// {
//     char *tmp = *buf;
//     *buf = ft_strjoin_c(tmp, c);
//     free(tmp);
// }

// static void handle_non_meta(char *input, int *i, char **buf, t_flag *flag)
// {
//     if (flag->quo == 0)
//     {
//         if (input[*i] == '\"')
//             flag->quo = DOUBLE_Q;
//         else if (input[*i] == '\'')
//             flag->quo = SINGLE_Q;
//         else if (input[*i] == '$')
//             flag->env = 1;
//     }
//     else
//     {
//         if (input[*i] == '\"' && flag->quo == DOUBLE_Q)
//             flag->quo = 0;
//         else if (input[*i] == '\'' && flag->quo == SINGLE_Q)
//             flag->quo = 0;
//     }
//     if (flag->quo == DOUBLE_Q && input[*i] == '$')
//         flag->env_with_quo = 1;
    
//     add_to_buffer(buf, input[*i]);
// }

// static void handle_buf_meta(char **buf, t_flag *flag, t_list *list)
// {
//     if ((*buf)[0] != 0)
//     {
//         make_node(*buf, *flag, list);
//         flag->env = 0;
//         flag->env_with_quo = 0;
//     }
// }

// static void handle_meta(char *input, int *i, char **buf, t_flag *flag)
// {
//     if (flag->quo)
//         exit(1);
//     handle_buf_meta(buf, flag, list);
//     if (input[*i] != ' ')
//     {
//         char *tmp;
//         if (input[*i + 1] && ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>' && input[*i + 1] == '>')))
//         {
//             tmp = ft_strndup(&input[*i], 2);
//             (*i)++;
//         }
//         else
//             tmp = ft_strndup(&input[*i], 1);
//         free(*buf);
//         *buf = tmp;
//         make_node(*buf, *flag, list);
//     }
// }

// void get_token(char *input, t_list *list)
// {
//     int     i;
//     char    *buf;
//     t_flag  flag;

//     i = 0;
//     init_flag(&flag);
//     buf = ft_strdup("");
//     while (input[i])
//     {
//         if (!is_meta(input[i]))
//             handle_non_meta(input, &i, &buf, &flag);
//         else if (is_meta(input[i]) && flag.quo > 0)
//             add_to_buffer(&buf, input[i]);
//         else
//             handle_meta(input, &i, &buf, &flag);
//         i++;
//     }
//     if (buf[0] != 0)
//         make_node(buf, flag, list);
//     free(buf);
// }


// 2차 수수정  코드
// static void	handle_buffer(char **buf, char c)
// {
// 	char	*tmp;

// 	tmp = *buf;
// 	*buf = ft_strjoin_c(tmp, c);
// 	free(tmp);
// }

// static void	init_flag(t_flag *flag)
// {
// 	flag->quo = 0;
// 	flag->env = 0;
// 	flag->env_with_quo = 0;
// }

// static void	handle_meta_char(char *input, int *i, char **buf, t_list *list)
// {
// 	char	*tmp;
// 	t_flag	flag;

// 	init_flag(&flag);

// 	if (input[*i + 1] && input[*i] == '<' && input[*i + 1] == '<')
// 	{
// 		tmp = ft_strndup(&input[*i], 2);
// 		(*i)++;
// 	}
// 	else if (input[*i + 1] && input[*i] == '>' && input[*i + 1] == '>')
// 	{
// 		tmp = ft_strndup(&input[*i], 2);
// 		(*i)++;
// 	}
// 	else
// 		tmp = ft_strndup(&input[*i], 1);

// 	*buf = ft_strjoin_c(tmp, input[*i]);
// 	make_node(*buf, flag, list);
// 	free(tmp);
// 	free(*buf);
// 	*buf = ft_strdup("");
// }

// void	get_token(char *input, t_list *list)
// {
// 	int		i;
// 	char	*buf;
// 	t_flag	flag;

// 	i = 0;
// 	init_flag(&flag);
// 	buf = ft_strdup("");

// 	while (input[i])
// 	{
// 		if (input[i] != ' ')
// 		{
// 			if (is_meta(input[i]) && flag.quo == 0)
// 				handle_meta_char(input, &i, &buf, list);
// 			else
// 			{
// 				handle_buffer(&buf, input[i]);
// 				if (flag.quo == 0 && (input[i] == '\"' || input[i] == '\''))
// 					flag.quo = (input[i] == '\"') ? 1 : 2;
// 				else if (flag.quo != 0 && (input[i] == '\"' || input[i] == '\''))
// 					flag.quo = 0;
// 			}
// 		}
// 		i++;
// 	}
// 	if (flag.quo != 0)
// 		exit(1); // or handle error
// 	if (buf[0] != 0)
// 		make_node(buf, flag, list);
// 	free(buf);
// }

// void append_character_to_buffer(char c, char **buf) {
//     char *tmp = *buf;
//     *buf = ft_strjoin_c(tmp, c);
//     free(tmp);
// }

// void process_normal_character(char c, t_flag *flag, char **buf) {
//     if (flag->quo == 0) {
//         if (c == '\"')
//             flag->quo = DOUBLE_Q;
//         else if (c == '\'')
//             flag->quo = SINGLE_Q;
//         else if (c == '$')
//             flag->env = 1;
//     } else {
//         if (c == '\"' && flag->quo == DOUBLE_Q)
//             flag->quo = 0;
//         else if (c == '\'' && flag->quo == SINGLE_Q)
//             flag->quo = 0;
//     }
//     if (flag->quo == DOUBLE_Q && c == '$')
//         flag->env_with_quo = 1;
//     char *tmp = *buf;
//     *buf = ft_strjoin_c(tmp, c);
//     free(tmp);
// }

// void process_meta_character(char c, t_flag flag, char **buf, t_list *list) {
//     char *tmp = *buf;
//     *buf = ft_strjoin_c(tmp, c);
//     free(tmp);
//     if (!flag.quo)
//         exit(1);
//     if ((*buf)[0] != 0) {
//         make_node(*buf, flag, list);
//         flag.env = 0;
//         flag.env_with_quo = 0;
//     }
//     if (c != ' ') {
//         if (input[i + 1] && ((c == '<' && input[i + 1] == '<') || (c == '>' && input[i + 1] == '>'))) {
//             tmp = ft_strndup(&input[i], 2);
//             i++;
//         } else
//             tmp = ft_strndup(&input[i], 1);
//         *buf = ft_strjoin_c(tmp, c);
//         free(tmp);
//         make_node(*buf, flag, list);
//     }
//     free(*buf);
//     *buf = ft_strdup("");
// }

// void get_token(char *input, t_list *list) {
//     int i = 0;
//     char *buf = ft_strdup("");
//     t_flag flag = {0, 0, 0}; // Initialize flag fields

//     while (input[i]) {
//         if (!is_meta(input[i]))
//             process_normal_character(input[i], &flag, &buf);
//         else if (is_meta(input[i]) && flag.quo > 0)
//             append_character_to_buffer(input[i], &buf);
//         else {
//             process_meta_character(input[i], flag, &buf, list);
//         }
//         i++;
//     }
//     if (flag.quo)
//         exit(1);
//     if (buf[0] != 0)
//         make_node(buf, flag, list);
//     free(buf);
// }

void	handle_quotes(char input, t_flag *flag)
{
	if (flag->quo == 0)
	{
		if (input == '\"')
			flag->quo = DOUBLE_Q;
		else if (input == '\'')
			flag->quo = SINGLE_Q;
		else if (input == '$')
			flag->env = 1;
	}
	else
	{
		if (input == '\"' && flag->quo == DOUBLE_Q)
			flag->quo = 0;
		else if (input == '\'' && flag->quo == SINGLE_Q)
			flag->quo = 0;
	}
	if (flag->quo == DOUBLE_Q && input == '$')
		flag->env_with_quo = 1;
}

char	*append_char_and_free(char *buf, char input)
{
	char	*tmp;

	tmp = buf;
	buf = ft_strjoin_c(tmp, input);
	free(tmp);
	return (buf);
}

void	check_make_node(char *buf, t_flag *flag, t_list *list)
{
	if (buf[0] != 0)
	{
		make_node(buf, *flag, list);
		flag->env = 0;
		flag->env_with_quo = 0;
	}
}

void	handle_special_char(char *input, int *i, t_flag flag, t_list *list)
{
	char	*tmp;
	char 	*buf;

	if (input[*i] != ' ')
	{
		if (input[*i + 1] && ((input[*i] == '<' && input[*i + 1] == '<') 
			|| (input[*i] == '>' && input[*i + 1] == '>')))
		{
			tmp = ft_strndup(&input[*i], 2);
			(*i)++;
		}
		else
			tmp = ft_strndup(&input[*i], 1);
		buf = ft_strjoin_c(tmp, input[*i]);
		free(tmp);
		make_node(buf, flag, list);
	}
	free(buf);
}
void	get_token(char *input, t_list *list)
{
	int		i;
	char	*buf;
	t_flag	flag;

	init_flag(&flag);
	buf = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (!is_meta(input[i]))
		{
			handle_quotes(input[i], &flag);
			buf = append_char_and_free(buf, input[i]);
		}
		else if (is_meta(input[i]) && flag.quo > 0)
			buf = append_char_and_free(buf, input[i]);
		else
		{
			if (flag.quo)
				exit(1);
			check_make_node(buf, &flag, list);
			handle_special_char(input, &i, flag, list);
			buf = ft_strdup("");
		}
		i++;
	}
	if (flag.quo)
		exit(1);
	check_make_node(buf, &flag, list);
	free(buf);
}
