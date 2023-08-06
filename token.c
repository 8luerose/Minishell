/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:05 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 16:29:46 by seojchoi         ###   ########.fr       */
=======
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:05 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/05 15:40:24 by taehkwon         ###   ########.fr       */
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
=======
// <<, >>ㅊㅓ리. 오류문구출력하면서 노드 free, syntax error + 확장 도전

// int	is_meta(char c1, char c2)
// {
// 	if (c1 == ' ' || c1 == '|' || c1 == '<' || c1 == '>')
// 		return (1);
// 	if ((c1 == '<' && c2 == '<') || (c1 == '>' && c2 == '>'))
// 		return (1);
// 	return (0);
// }

// int	is_meta(char c)
// {
// 	if (c == ' ' || c == '|'
// 		|| c == '<' || c == '>' || c == "<<" || c == ">>")
// 		return (1);
// 	return (0);
// }

>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
int	is_meta(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

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
<<<<<<< HEAD
			buf = ft_strjoin_c(tmp, input[i]);
=======
			buf = ft_strjoin(tmp, input[i]);
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
			free(tmp);
		}
		else if (is_meta(input[i]) && flag.quo > 0)
		{
			tmp = buf;
<<<<<<< HEAD
			buf = ft_strjoin_c(tmp, input[i]);
=======
			buf = ft_strjoin(tmp, input[i]);
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
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
				if (input[i + 1] && ((input[i] == '<' && input[i+1] == '<') || (input[i] == '>' && input[i+1] == '>'))) 
				{
					tmp = ft_strndup(&input[i], 2);
					i++;
				}
				else
				{
					tmp = ft_strndup(&input[i], 1);
				}
<<<<<<< HEAD
				buf = ft_strjoin_c(tmp, input[i]);
=======
				buf = ft_strjoin(tmp, input[i]);
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
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
	make_node(buf, flag, list);
	free(buf);
}
