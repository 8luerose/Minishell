/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:29:48 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 16:30:13 by seojchoi         ###   ########.fr       */
=======
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:29:48 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/05 16:43:07 by taehkwon         ###   ########.fr       */
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
char	*ft_strjoin_c(char const *s1, char c)    // 문자 하나 조인
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
=======
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
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
	return (new);
}

char	*ft_strndup(const char *s1, int n)
{
	int		size;
	char	*new;

	size = 0;
	while (s1[size] && size < n-1)
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

<<<<<<< HEAD
=======
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

>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
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
<<<<<<< HEAD
}
=======
}
>>>>>>> 8a1560c44087f9d5c10bd7e32421d962996889ed
