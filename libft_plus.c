/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:29:48 by seojchoi          #+#    #+#             */
/*   Updated: 2023/09/09 04:51:03 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_c(char const *s1, char c)
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

char	*ft_strndup(const char *s1, int n)
{
	int		size;
	char	*new;

	size = 0;
	while (s1[size] && size < n - 1)
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	case1;
	unsigned char	case2;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		case1 = (unsigned char)s1[i];
		case2 = (unsigned char)s2[i];
		if (case1 != case2)
			return (case1 - case2);
		i++;
	}
	return (0);
}
