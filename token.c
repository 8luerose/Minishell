/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:05 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/04 20:36:05 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	add_buffer(char **buf, char c)
// {
//     char    *tmp;

//     tmp = *buf;
//     *buf = ft_strjoin_c(tmp, c);
//     free(tmp);
// }

// void	non_meta(char **buf, char *input, int *i, char *quo)
// {
//     if (*(quo) == 0 && (input[*(i)] == '\'' || input[*(i)] == '\"'))
//         *(quo) = input[*(i)];
//     else if (input[*(i)] == *quo)
//         *(quo) = 0;
//     add_buffer(buf, input[*(i)]);
// }

// void	ok_meta(char **buf, char *input, int *i, t_list *list)
// {
//     if ((*buf)[0] != 0)
//         make_node(*buf, list);
//     if (input[*i] != ' ')
//     {
//         char *(tmp);
//         if (input[*(i) + 1] 
// 			&& ((input[*(i)] == '<' && input[*(i) + 1] == '<') 
// 			|| (input[*(i)] == '>' && input[*(i) + 1] == '>')))
//         {
//             tmp = ft_strndup(&input[*(i)], 2);
//             (*i)++;
//         }
//         else
//             tmp = ft_strndup(&input[*(i)], 1);
//         *(buf) = ft_strjoin_c(tmp, input[*(i)]);
//         free(tmp);
//         make_node(*(buf), list);
//     }
//     free(*(buf));
//     *(buf) = ft_strdup("");
// }

// void	get_token(char *input, t_list *list)
// {
//     int     i;
//     char    quo;
//     char    *buf;

//     i = 0;
//     quo = 0;
//     buf = ft_strdup("");
//     while (input[i])
//     {
//         if (!is_meta(input[i]))
//             non_meta(&buf, input, &i, &quo);
//         else if (is_meta(input[i]) && quo != 0)
//             add_buffer(&buf, input[i]);
//         else
//             ok_meta(&buf, input, &i, list);
//         i++;
//     }
//     if (quo != 0)
//         exit(0);
//     if (buf[0] != 0)
//         make_node(buf, list);
//     free(buf);
// }

int	is_escape(char *input, int i, char quo)
{
	if (input[i] == '\\')
	{
		if (input[i + 1] && quo != '\'' &&  (input[i + 1] == 'n' || input[i + 1] == '\'' || input[i + 1] == '\"'))
			return (1);
	}
	return (0);
}

int	is_meta(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	get_token(char *input, t_list *list)
{
	int		i;
	char	quo;
	char	*buf;
	char	*tmp;

	i = 0;
	quo = 0;
	buf = ft_strdup("");
	while (input[i])
	{
		if (!is_meta(input[i]))
		{
			if (is_escape(input, i, quo))
			{
				tmp = buf;
				buf = ft_strjoin_c(tmp, input[i]);
				free(tmp);
				i++;
			}
			else if (quo == 0 && (input[i] == '\'' || input[i] == '\"'))
				quo = input[i];
			else if (input[i] == quo)
				quo = 0;
			tmp = buf;
			buf = ft_strjoin_c(tmp, input[i]);
			free(tmp);
		}
		else if (is_meta(input[i]) && quo != 0)
		{
			tmp = buf;
			buf = ft_strjoin_c(tmp, input[i]);
			free(tmp);
		}
		else
		{
			if (buf[0] != 0)
				make_node(buf, list);
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
				make_node(buf, list);
			}
			free(buf);
			buf = ft_strdup("");
		}
		i++;
	}
	if (quo != 0)
	{
		// quo_error();  // 추가하기
		return (0);
	}
	if (buf[0] != 0)
		make_node(buf, list);
	free(buf);
	return (1);
}
