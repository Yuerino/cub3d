/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:17:55 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 19:00:32 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Get the texture data from line
 * @param line Line contains path of texture
 * @param texture Struct for the texture data
 * @return 1 if success otherwise 0
 */
static int	get_texture(t_cub3d *data, char *line, t_image *texture)
{
	char	**splited;

	splited = ft_split(line, ' ');
	if (!splited)
		return (print_perror("ft_split"));
	if (carray_len(splited) != 2)
	{
		free_carray(splited);
		return (print_error("Error: Invalid texture data"));
	}
	texture->img_ptr = mlx_xpm_file_to_image(data->mlx, splited[1],
			texture->width, texture->height);
	if (!texture->img_ptr)
	{
		free_carray(splited);
		return (print_error(""));
	}
	return (1);
}

/** @todo: too long, not norm
 * @brief Get the color data from line
 * @param line Line that has RGB color data
 * @param color Integer array size of 3 for R, G, B value
 * @return 1 if success otherwise 0
 */
static int	get_color(t_cub3d *data, char *line, int **color)
{
	char	**splited;
	char	**color_split;

	splited = ft_split(line, ' ');
	if (!splited)
		return (print_perror("ft_split"));
	if (carray_len(splited) != 2)
	{
		free_carray(splited);
		return (print_error("Error: Invalid color data"));
	}
	color_split = ft_split(splited[1], ',');
	if (!color_split)
	{
		free_carray(splited);
		return (print_perror("ft_split"));
	}
	if (carray_len(color_split) != 3)
	{
		free_carray(splited);
		free_carray(color_split);
		return (print_error("Error: Invalid color data"));
	}
	(*color)[0] = ft_atoi(color_split[0]);
	(*color)[1] = ft_atoi(color_split[1]);
	(*color)[2] = ft_atoi(color_split[2]);
	if (!is_color_valid(*color))
	{
		free_carray(splited);
		free_carray(color_split);
		return (print_error("Error: Invalid color data"));
	}
	return (1);
}

/**
 * @brief Validate line from map file and parse it into respectively data
 * @param fd map file descriptor for closing in case error
 */
static void	process_line(t_cub3d *data, char *line, int fd)
{
	int	ret;

	if (!ft_strncmp(line, "NO ", 3))
		ret = get_texture(data, line, &data->map.north);
	else if (!ft_strncmp(line, "SO ", 3))
		ret = get_texture(data, line, &data->map.south);
	else if (!ft_strncmp(line, "WE ", 3))
		ret = get_texture(data, line, &data->map.west);
	else if (!ft_strncmp(line, "EA ", 3))
		ret = get_texture(data, line, &data->map.east);
	else if (!ft_strncmp(line, "F ", 2))
		ret = get_color(data, line, &data->map.floor_color);
	else if (!ft_strncmp(line, "C ", 2))
		ret = get_color(data, line, &data->map.ceiling_color);
	else if (is_map_line(line))
		ret = 1;
	else if (!ft_strlen(line))
		ret = 1;
	if (!ret)
	{
		free(line);
		close(fd);
		free_data(data);
		exit(EXIT_FAILURE);
	}
}

void	read_map(t_cub3d *data, char *filename)
{
	int		fd;
	char	*line;

	if (!is_ext_valid(filename))
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
