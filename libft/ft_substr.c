/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:07:56 by seojchoi          #+#    #+#             */
/*   Updated: 2023/03/18 13:06:39 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	check_size(unsigned int size, unsigned int start, size_t len)
{
	if (size - start == len)
		return (len);
	else if (size - start > len)
		return (len);
	else
		return (size - start);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*tmp;
	unsigned int		size;

	if (!s)
		return (0);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	size = check_size(size, start, len);
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	if (tmp == 0)
		return (0);
	ft_strlcpy(tmp, &s[start], size + 1);
	return (tmp);
}
