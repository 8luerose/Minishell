/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:14:27 by seojchoi          #+#    #+#             */
/*   Updated: 2023/03/18 13:13:24 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*u_dst;
	unsigned char	*u_src;
	size_t			i;

	u_dst = (unsigned char *)dst;
	u_src = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (dst < src)
	{
		i = -1;
		while (++i < len)
			u_dst[i] = u_src[i];
	}
	else
	{
		i = -1;
		while (++i < len)
			u_dst[len - i - 1] = u_src[len - i - 1];
	}
	return (dst);
}
