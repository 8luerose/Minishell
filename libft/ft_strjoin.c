/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:25:54 by seojchoi          #+#    #+#             */
/*   Updated: 2023/08/06 15:14:58 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_s;
	size_t	s2_s;
	size_t	i;
	size_t	j;
	char	*new;

	s1_s = ft_strlen(s1);
	s2_s = ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (s1_s + s2_s + 1));
	if (new == 0)
		return (0);
	i = 0;
	while (i < s1_s)
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_s)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}
