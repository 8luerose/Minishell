/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:29:48 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/05 15:22:09 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*new;

	size = 0;
	while (s1[size])
		size++;
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (new == 0)
		return (0);
	new[size--] = '\0';
	while (size >= 0)
	{
		new[size] = s1[size];
		size--;
	}
	return (new);
}

char	*ft_strndup(const char *s1, int n)
{
	int		size;
	char	*new;

	size = 0;
	while (s1[size] && size < n)
		size++;
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (new == 0)
		return (0);
	new[size--] = '\0';
	while (size >= 0)
	{
		new[size] = s1[size];
		size--;
	}
	return (new);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char c)
{
	size_t	s1_s;
	size_t	i;
	char	*new;

	s1_s = ft_strlen(s1);
	new = (char *)malloc(sizeof(char) * (s1_s + 2));
	if (new == 0)
		return (0);
	i = 0;
	while (i < s1_s)
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	return (new);
}
