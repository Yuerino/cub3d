/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:39:08 by cthien-h          #+#    #+#             */
/*   Updated: 2022/01/26 21:31:54 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_line(char **save, int fd)
{
	char	*buffer;
	int		read_size;
	char	*tmp;

	read_size = 0;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	while (!*save || !(ft_strchr(*save, '\n')))
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 1)
			break ;
		*(buffer + read_size) = '\0';
		if (*save)
		{
			tmp = ft_strjoin(*save, buffer);
			free(*save);
			*save = tmp;
		}
		else
			*save = ft_strdup(buffer);
	}
	free(buffer);
	return (read_size);
}

static char	*split_newline(char **save, int newline_index)
{
	char	*tmp;
	char	*line;

	(*save)[newline_index] = '\0';
	line = ft_strdup(*save);
	if (!ft_strlen(*save + newline_index + 1))
	{
		free(*save);
		*save = NULL;
	}
	else
	{
		tmp = ft_strdup(*save + newline_index + 1);
		free(*save);
		*save = tmp;
	}
	return (line);
}

static char	*return_line(char **save)
{
	char	*line;

	if (*save && ft_strchr(*save, '\n'))
	{
		return (split_newline(save, ft_strchr(*save, '\n') - *save));
	}
	else if (*save)
	{
		line = *save;
		*save = NULL;
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*saves[MAX_OPEN_FD];
	int			read_size;

	if (fd < 0 || fd >= MAX_OPEN_FD || BUFFER_SIZE < 0)
		return (NULL);
	read_size = read_line(&saves[fd], fd);
	if (read_size < 0)
		return (NULL);
	return (return_line(&saves[fd]));
}
