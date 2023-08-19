/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:29:57 by seojchoi          #+#    #+#             */
/*   Updated: 2023/03/20 17:44:03 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cnt_size(long long n)
{
	int	cnt;

	cnt = 0;
	if (n < 0)
	{
		n *= -1;
		cnt ++;
		cnt += cnt_size (n);
		return (cnt);
	}
	while (n >= 1)
	{
		n /= 10;
		cnt ++;
	}
	return (cnt);
}

char	*allocate_num(char *tmp, int size, long long n)
{
	if (n < 0)
	{
		n *= -1;
		tmp[0] = '-';
	}
	while (n >= 1 && size - 1 >= 0)
	{
		tmp[size - 1] = n % 10 + '0';
		n /= 10;
		size --;
	}
	return (tmp);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*tmp;

	if (n == 0)
	{
		tmp = (char *)malloc(sizeof(char) * 2);
		if (tmp == 0)
			return (0);
		tmp[0] = '0';
		tmp[1] = '\0';
		return (tmp);
	}
	size = cnt_size((long long)n);
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	if (tmp == 0)
		return (0);
	tmp = allocate_num(tmp, size, (long long)n);
	tmp[size] = '\0';
	return (tmp);
}
