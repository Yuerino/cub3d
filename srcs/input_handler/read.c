/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:17:55 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 01:35:25 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the map file has correct extension .cub
 * @param filename Path to the cub3d map
 * @return 1 if yes otherwise 0
 */
static int	is_file_format(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, ".cub", 5))
		return (0);
	return (1);
}

/**
 * @todo: in progress
 * @brief Validate line from map file and parse into data struct
 * @param fd map file descriptor for closing in case error
 */
static void	process_line(t_cub3d *data, char *line, int fd)
{
	(void)data;
	(void)fd;
	printf("%s\n", line);
}

void	read_map(t_cub3d *data, char *filename)
{
	int		fd;
	char	*line;

	if (!is_file_format(filename))
		exit_error("Error: Wrong file format!", data);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_perror(filename, data);
	line = get_next_line(fd);
	while (line)
	{
		process_line(data, line, fd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
