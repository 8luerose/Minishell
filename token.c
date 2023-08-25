/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:05 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/24 21:42:20 by taehkwon         ###   ########.fr       */
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
// 	if (input[*i] != ' ')
// 	{
// 		if (input[*i + 1] && ((input[*i] == '<' && input[*i + 1] == '<') || \
// 			(input[*i] == '>' && input[*i + 1] == '>')))
// 		{
// 			tmp = ft_strndup(&input[*i], 2);
// 			(*i)++;
// 		}
// 		else
// 			tmp = ft_strndup(&input[*i], 1);
// 		*buf = ft_strjoin_c(tmp, input[*i]);
// 		free(tmp);
// 		make_node(*buf, *flag, list);
// 	}
// 	free(*buf);
// 	*buf = ft_strdup("");
// }

// // 1차 수정 코드
// // void	get_token(char *input, t_list *list)
// // {
// // 	int		i = 0;
// // 	char	*buf = ft_strdup("");
// // 	t_flag	flag;

// // 	init_flag(&flag);  // 초기화 함수 추가
// // 	while (input[i])
// // 	{
// // 		if (!is_meta(input[i]))
// // 		{
// // 			update_flags(input[i], &flag);
// // 			char *tmp = buf;
// // 			buf = ft_strjoin_c(tmp, input[i]);
// // 			free(tmp);
// // 		}
// // 		else if (is_meta(input[i]) && flag.quo > 0)
// // 		{
// // 			char *tmp = buf;
// // 			buf = ft_strjoin_c(tmp, input[i]);
// // 			free(tmp);
// // 		}
// // 		else
// // 			handle_meta(input, &i, &buf, &flag, list);
// // 		i++;
// // 	}
// // 	if (flag.quo)
// // 		exit(1);
// // 	if (buf[0] != 0)
// // 		make_node(buf, flag, list);
// // 	free(buf);
// // }


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
