/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:17:55 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/17 16:13:32 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Helper function to print error for get_texture and get_color
 * and (optional) free double char pointer arr
 * @param err (Optional) Error message, if empty,
 * will print errno message instead
 * @param perr (Optional) Additional error message for errno
 * @param arr (Optional) Double char pointer to be freed
 * @return 0 for error
 */
int	print_read_error(t_cub3d *data, char *err, char *perr, char **arr)
{
	if (err)
		print_error(err, data);
	else
		print_perror(perr, data);
	if (arr)
		free_carray(arr);
	return (0);
}

/**
 * @brief Get the color data from line and free the line
 * @param line Line that has RGB color data
 * @param color Pointer of the color you want to set to
 * @return 1 if success otherwise 0
 */
static int	get_color(t_cub3d *data, char *line, long long *color)
{
	char	**splited;
	char	**color_split;

	splited = ft_split(line, ' ');
	free(line);
	if (!splited)
		return (print_perror("ft_split", data));
	if (carray_len(splited) != 2)
		return (print_read_error(data, "Error\nInvalid color data",
				NULL, splited));
	color_split = ft_split(splited[1], ',');
	free_carray(splited);
	if (!color_split)
		return (print_perror("ft_split", data));
	if (carray_len(color_split) != 3
		|| !str_rgb_to_color(color_split[0], color_split[1], \
			color_split[2], color))
		return (print_read_error(data, "Error\nInvalid color data",
				NULL, color_split));
	free_carray(color_split);
	if ((&data->map.floor_color == color && data->map.ceiling_color == *color)
		|| (&data->map.ceiling_color == color
			&& data->map.floor_color == *color))
		return (print_error("Error\nDuplicated color", data));
	return (1);
}

/**
 * @brief Validate line and parse it into respectively data
 * if it hasn't been parsed before then free the line
 * @param fd Map file descriptor for closing in case error
 * @return 1 if success otherwise 0
 */
static int	process_line(t_cub3d *data, char *line, int fd)
{
	if (!ft_strncmp(line, "NO ", 3) && !data->map.north.img_ptr)
		return (get_texture(data, line, &data->map.north));
	else if (!ft_strncmp(line, "SO ", 3) && !data->map.south.img_ptr)
		return (get_texture(data, line, &data->map.south));
	else if (!ft_strncmp(line, "WE ", 3) && !data->map.west.img_ptr)
		return (get_texture(data, line, &data->map.west));
	else if (!ft_strncmp(line, "EA ", 3) && !data->map.east.img_ptr)
		return (get_texture(data, line, &data->map.east));
	else if (!ft_strncmp(line, "F ", 2) && data->map.floor_color == INT64_MAX)
		return (get_color(data, line, &data->map.floor_color));
	else if (!ft_strncmp(line, "C ", 2) && data->map.ceiling_color == INT64_MAX)
		return (get_color(data, line, &data->map.ceiling_color));
	else if (!data->map.data && (*line == ' ' || *line == '0' || *line == '1')
		&& data->map.north.img_ptr && data->map.south.img_ptr
		&& data->map.west.img_ptr && data->map.east.img_ptr
		&& data->map.floor_color != INT64_MAX
		&& data->map.ceiling_color != INT64_MAX)
		return (read_map(data, line, fd));
	print_error("Error\nInvalid map data", data);
	free(line);
	return (0);
}

/**
 * @brief Open map file and parse data line by line
 * and exit if fail to parse
 * @param filename Path to the map file
 */
void	read_file_data(t_cub3d *data, char *filename)
{
	int		fd;
	char	*line;
	int		ret;

	if (!is_ext_valid(filename, ".cub"))
		exit_error("Error\nWrong file format!", data);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_perror(filename, data);
	line = get_next_line(fd);
	ret = 1;
	while (line)
	{
		if (!ret || !ft_strlen(line))
			free(line);
		else if (ret)
			ret = process_line(data, line, fd);
		line = get_next_line(fd);
	}
	close(fd);
	if (!ret)
		exit(EXIT_FAILURE);
}
