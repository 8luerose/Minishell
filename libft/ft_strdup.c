/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:08:23 by seojchoi          #+#    #+#             */
/*   Updated: 2023/03/17 15:54:37 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
