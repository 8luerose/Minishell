/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:07:18 by seojchoi          #+#    #+#             */
/*   Updated: 2023/03/19 16:25:24 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(char const *s, char c)
{
	int	i;
	int	flag;
	int	word_cnt;

	i = 0;
	flag = 0;
	word_cnt = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			flag = 1;
			i++;
		}
		if (flag == 1)
		{
			word_cnt++;
			flag = 0;
		}
	}
	return (word_cnt);
}

void	allocate_word(char *dst, int idx, int cnt, char const *s)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		dst[i] = s[idx + i];
		i++;
	}
	dst[i] = 0;
}

char	*separate_word(int idx, char const *s, char c)
{
	int		cnt;
	char	*malloc_temp;

	cnt = 0;
	while (s[idx + cnt] != c && s[idx + cnt] != 0)
		cnt++;
	malloc_temp = (char *)malloc(sizeof(char) * (cnt + 1));
	if (!malloc_temp)
		return (0);
	allocate_word(malloc_temp, idx, cnt, s);
	return (malloc_temp);
}

char	**freeall(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		idx;
	int		word_cnt;
	char	**result;

	word_cnt = count(s, c);
	result = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!result)
		return (0);
	idx = 0;
	i = 0;
	while (s[idx] != 0 && i < word_cnt)
	{
		while (s[idx] == c && s[idx] != 0)
			idx++;
		result[i] = separate_word(idx, s, c);
		if (result[i++] == 0)
			return (freeall(result));
		while (s[idx] != c && s[idx] != 0)
			idx++;
	}
	result[word_cnt] = 0;
	return (result);
}
