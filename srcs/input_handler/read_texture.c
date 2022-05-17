/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 06:42:12 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/17 16:12:49 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @note Yes I know there's easier way but I'm too lazy
 * @brief Check if same texture file has already loaded
 * @param texture The texture's used for compare
 * @return 1 if duplicate otherwise 0
 */
static int	check_texture_dup(t_cub3d *data, t_map *map, t_image *texture)
{
	if ((&map->north != texture && map->north.filename && !ft_strncmp \
		(map->north.filename, texture->filename, ft_strlen(texture->filename)))
		|| (&map->south != texture && map->south.filename && !ft_strncmp \
		(map->south.filename, texture->filename, ft_strlen(texture->filename)))
		|| (&map->west != texture && map->west.filename && !ft_strncmp \
		(map->west.filename, texture->filename, ft_strlen(texture->filename)))
		|| (&map->east != texture && map->east.filename && !ft_strncmp \
		(map->east.filename, texture->filename, ft_strlen(texture->filename))))
		return (print_error("Error\nDuplicated texture", data));
	return (1);
}

/**
 * @brief Get the texture data from line and free the line
 * @param line Line contains path of texture
 * @param texture Struct for the texture data
 * @return 1 if success otherwise 0
 */
int	get_texture(t_cub3d *data, char *line, t_image *texture)
{
	char	**splited;

	splited = ft_split(line, ' ');
	free(line);
	if (!splited)
		return (print_perror("ft_split", data));
	if (carray_len(splited) != 2)
		return (print_read_error(data, "Error\nInvalid texture data",
				NULL, splited));
	if (!is_ext_valid(splited[1], ".xpm"))
		return (print_read_error(data, "Error\nInvalid texture file extension",
				NULL, splited));
	texture->img_ptr = mlx_xpm_file_to_image(data->mlx, splited[1],
			&texture->width, &texture->height);
	texture->filename = ft_strrchr(splited[1], '/');
	if (!texture->filename)
		texture->filename = ft_strdup(splited[1]);
	else
		texture->filename = ft_strdup(++texture->filename);
	if (!texture->img_ptr || !texture->filename)
		return (print_read_error(data, NULL, splited[1], splited));
	free_carray(splited);
	return (check_texture_dup(data, &data->map, texture));
}
