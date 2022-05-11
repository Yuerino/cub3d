/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:22:27 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/11 02:46:25 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialise mlx and create a window
 */
static void	init_mlx(t_cub3d *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_perror("mlx", NULL);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->win)
		exit_perror("window", data);
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
}

/**
 * @brief Initialise player struct
 */
static void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->dir_x = 0.0f;
	player->dir_y = 0.0f;
}

/**
 * @brief Initialise cub3d main struct and its elements
 * and read map data from file *
 * @param filename Path to map file
 */
void	init_cub3d(t_cub3d *data, char *filename)
{
	init_mlx(data);
	init_map(&data->map);
	init_player(&data->player);
	read_file_data(data, filename);
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
	if (data->map.data)
		free_carray(data->map.data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
