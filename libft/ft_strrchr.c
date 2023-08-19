/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:58:27 by seojchoi          #+#    #+#             */
/*   Updated: 2023/03/18 13:05:42 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	find;
	char	*start;

	find = (char)c;
	start = (char *)s;
	while (*s)
		s++;
	while (s != start)
	{
		if (*s == find)
			return ((char *)s);
		s--;
	}
	if (*s == find)
		return ((char *)s);
	return (0);
}
