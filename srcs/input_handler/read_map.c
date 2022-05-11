/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:13:54 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/11 16:38:49 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Helper function to print error for read_map functions
 * and (optional) free double char array
 * @param err (Optional) Error message, if empty,
 * will print errno message instead
 * @param perr (Optional) Additional error message for errno
 * @param line (Optional) Char array to be freed
 * @return 0 for error
 */
static int	print_read_map_error(t_cub3d *data, char *err, char *perr,
	char *line)
{
	if (err)
		print_error(err, data);
	else
		print_perror(perr, data);
	free(line);
	return (0);
}

/**
 * @brief Set the player x position and facing direction
 * @param c Direction of player
 * @param x Player x position
 * @return '0' for empty space in map
 */
static char	set_player_pos(t_player *player, char c, int x)
{
	player->x = (double)x;
	if (c == 'N')
		player->dir_y = 1.0f;
	else if (c == 'S')
		player->dir_y = -1.0f;
	else if (c == 'E')
		player->dir_x = 1.0f;
	else if (c == 'W')
		player->dir_x = -1.0f;
	return ('0');
}

/**
 * @brief Get the correct map character at that point
 * or get and set player x position and facing direction if it's a player
 * @param line Map line that has the character
 * @param x x-coordinate (index) of that line that you want to get from
 * @return char Map character ('0', '1', ' ') or 0 if error
 */
static char	read_map_point(t_cub3d *data, char *line, int x)
{
	if (line[x] == '0' || line[x] == '1' || line[x] == ' ')
		return (line[x]);
	else if (line[x] == 'N' || line[x] == 'S'
		|| line[x] == 'E' || line[x] == 'W')
		return (set_player_pos(&data->player, line[x], x));
	return (print_read_map_error(data, "Error: Invalid map data", NULL, line));
}

/**
 * @brief Read and parse map line into map data
 * @param line Map line to be parsed
 * @param y y-coordinate of this line in the map
 * @return 1 if success otherwise 0
 */
static int	read_map_line(t_cub3d *data, char *line, int y)
{
	int		x;
	char	c;

	data->map.data = carray_expand(data->map.data);
	if (!data->map.data)
		return (print_read_map_error(data, NULL, "carray_expand", line));
	data->map.data[y] = ft_calloc(sizeof(char), ft_strlen(line) + 1);
	if (!data->map.data[y])
		return (print_read_map_error(data, NULL, "ft_calloc", line));
	x = 0;
	while (line[x])
	{
		c = read_map_point(data, line, x);
		if (c == 0)
			return (0);
		data->map.data[y][x] = c;
		x++;
	}
	if (x > data->map.max_width)
		data->map.max_width = x;
	if (data->player.x > 0 && data->player.y < 0)
		data->player.y = (double)y;
	free(line);
	return (1);
}

/**
 * @todo Check map is valid (surrounded by walls)
 * @brief Validate and parse map data line by line from file fd,
 * stop when EOF or empty line
 * @param line First line of the map data
 * @param fd Map file descriptor to read from
 * @return 1 if success otherwise 0
 */
int	read_map(t_cub3d *data, char *line, int fd)
{
	int	y;

	if (!read_map_line(data, line, 0))
		return (0);
	y = 1;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strlen(line))
		{
			free(line);
			break ;
		}
		if (!read_map_line(data, line, y))
			return (0);
		y++;
		line = get_next_line(fd);
	}
	data->map.height = y;
	// TODO: check map valid here
	return (1);
}
