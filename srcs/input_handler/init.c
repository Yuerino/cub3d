/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:22:27 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 05:16:42 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialise and create minimap
 */
static void	init_minimap(t_cub3d *data)
{
	int	square_size;

	if (data->map.max_width > data->map.height)
		square_size = (int)(WIN_WIDTH / data->map.max_width / 5);
	else
		square_size = (int)(WIN_HEIGHT / data->map.height / 5);
	data->minimap.width = data->map.max_width * square_size;
	data->minimap.height = data->map.height * square_size;
	data->minimap.img_ptr = mlx_new_image(data->mlx, \
		data->minimap.width, data->minimap.height);
	create_minimap(data);
}

/**
 * @brief Initialise map struct by setting all pointer to NULL
 */
static void	init_map(t_map *map)
{
	map->north.img_ptr = NULL;
	map->south.img_ptr = NULL;
	map->west.img_ptr = NULL;
	map->east.img_ptr = NULL;
	map->floor_color[0] = -1;
	map->ceiling_color[0] = -1;
	map->data = NULL;
	map->height = -1;
	map->max_width = -1;
}

/**
 * @brief Initialise player struct
 */
static void	init_player(t_player *player)
{
	player->x = -1.0f;
	player->y = -1.0f;
	player->dir_x = 0.0f;
	player->dir_y = 0.0f;
	player->speed = 0.1f;
}

/**
 * @brief Initialise cub3d main struct and its elements
 * and read map data from file *
 * @param filename Path to map file
 */
void	init_cub3d(t_cub3d *data, char *filename)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_perror("mlx", NULL);
	data->win = NULL;
	data->main_img = NULL;
	data->minimap.img_ptr = NULL;
	init_map(&data->map);
	init_player(&data->player);
	read_file_data(data, filename);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->win)
		exit_perror("window", data);
	data->main_img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	init_minimap(data);
	if (!data->main_img || !data->minimap.img_ptr)
		exit_perror("mlx_new_image", data);
	data->mouse_x = -1;
}

/**
 * @brief Free all allocated data inside data struct including those from mlx
 * @note This shouldn't belong to input handler so extract this
 * into new file if needed
 */
void	free_data(t_cub3d *data)
{
	if (data->map.north.img_ptr)
		mlx_destroy_image(data->mlx, data->map.north.img_ptr);
	if (data->map.south.img_ptr)
		mlx_destroy_image(data->mlx, data->map.south.img_ptr);
	if (data->map.west.img_ptr)
		mlx_destroy_image(data->mlx, data->map.west.img_ptr);
	if (data->map.east.img_ptr)
		mlx_destroy_image(data->mlx, data->map.east.img_ptr);
	if (data->main_img)
		mlx_destroy_image(data->mlx, data->main_img);
	if (data->minimap.img_ptr)
		mlx_destroy_image(data->mlx, data->minimap.img_ptr);
	if (data->map.data)
		free_carray(data->map.data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
