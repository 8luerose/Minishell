/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:16:25 by seojchoi          #+#    #+#             */
/*   Updated: 2023/07/27 14:08:37 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_ptr(char **ptr)
{
	free(*ptr);
	*ptr = 0;
}

char	*read_file(int fd, char *buf, char **backup)
{
	int		read_size;
	char	*tmp;

	while (!ft_strchr(*backup, '\n'))
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1 || read_size == 0)
			break ;
		buf[read_size] = '\0';
		if (!*backup)
		{
			*backup = ft_strdup("");
			if (*backup == 0)
				return (0);
		}
		tmp = *backup;
		*backup = ft_strjoin(tmp, buf);
		free_ptr(&tmp);
		if (*backup == 0)
			return (0);
	}
	if (read_size == -1)
		free_ptr(backup);
	return (*backup);
}

char	*make_backup(char *line)
{
	int		idx;
	char	*new_backup;

	idx = 0;
	while (line[idx] != '\0' && line[idx] != '\n')
		idx++;
	if (line[idx] == '\0' || line[idx + 1] == '\0')
		return (0);
	new_backup = ft_strdup(&line[idx + 1]);
	if (new_backup == 0)
		return (0);
	return (new_backup);
}

char	*make_line(char *line)
{
	int		idx;
	char	*res;

	idx = 0;
	while (line[idx] != '\0' && line[idx] != '\n')
		idx++;
	if (line[idx] == '\0')
		res = (char *)malloc(sizeof(char) * idx + 1);
	else
		res = (char *)malloc(sizeof(char) * idx + 2);
	if (res == 0)
		return (0);
	idx = 0;
	while (line[idx] && line[idx] != '\n')
	{
		res[idx] = line[idx];
		idx++;
	}
	if (line[idx] == '\n')
		res[idx++] = '\n';
	res[idx] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	char		*res;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == 0)
	{
		free_ptr(&backup);
		return (0);
	}
	line = read_file(fd, buf, &backup);
	free_ptr(&buf);
	if (line == 0)
		return (0);
	backup = make_backup(line);
	res = make_line(line);
	if (res == 0)
		free_ptr(&backup);
	free_ptr(&line);
	return (res);
}
