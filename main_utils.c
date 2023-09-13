/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 01:06:34 by taehkwon          #+#    #+#             */
/*   Updated: 2023/09/10 13:35:38 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_content(char	*line)
{
	int		i;
	int		size;
	char	*content;

	size = 0;
	while (line[size])
		size++;
	content = (char *)malloc(sizeof(char) * size + 1);
	if (!content)
		exit(1);
	i = 0;
	while (line[i])
	{
		content[i] = line[i];
		i++;
	}
	content[i] = '\0';
	return (content);
}

void	copy_envp(char	**ev, t_envp	*my_envp)
{
	int		i;
	char	*content;

	i = 0;
	while (ev[i])
	{
		content = make_content(ev[i]);
		make_node(content, my_envp->envp);
		free(content);
		i++;
	}
}
