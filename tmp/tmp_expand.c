/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_token2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 02:00:46 by taehkwon          #+#    #+#             */
/*   Updated: 2023/08/08 02:01:00 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_insert(char *str, char *to_insert, int start, int len_to_replace)
{
	char	*new_str;
	int		new_len;

	new_len = ft_strlen(str) - len_to_replace + ft_strlen(to_insert);
	new_str = (char *)malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	strncpy(new_str, str, start);
	strcpy(new_str + start, to_insert);
	strcat(new_str, str + start + len_to_replace);
	free(str);
	return (new_str);
}

char	*expand_env_vars(char *token)
{
	char	*start;
	char	*name;
	char	*value;
	int		len_name;

	start = strchr(token, '$');
	while (start)
	{
		name = start + 1;
		while (*name && (isalnum(*name) || *name == '_'))
			name++;
		len_name = name - (start + 1);
		value = getenv(strndup(start + 1, len_name));
		if (value)
		{
			token = str_insert(token, value, start - token, len_name + 1);
			if (!token)
				return (NULL);
		}
		start = strchr(name, '$');
	}
	return (token);
}
