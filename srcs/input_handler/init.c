/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:22:27 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 17:06:46 by cthien-h         ###   ########.fr       */
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
	map->south.img = NULL;
	map->south.img = NULL;
	map->west.img = NULL;
	map->east.img = NULL;
	map->map = NULL;
	map->height = -1;
}

void	init_cub3d(t_cub3d *data, char *filename)
{
	init_mlx(data);
	init_map(&data->map);
	read_map(data, filename);
}

/**
 * @brief Free all allocated data inside data struct including those from mlx
 * @note This shouldn't belong to input handler so extract this
 * into new file if needed
 */
void	free_data(t_cub3d *data)
{
	if (data->map.north.img)
		mlx_destroy_image(data->mlx, data->map.north.img);
	if (data->map.south.img)
		mlx_destroy_image(data->mlx, data->map.south.img);
	if (data->map.west.img)
		mlx_destroy_image(data->mlx, data->map.west.img);
	if (data->map.east.img)
		mlx_destroy_image(data->mlx, data->map.east.img);
	while (data->map.map && data->map.height-- >= 0)
		free(data->map.map[data->map.height]);
	if (data->map.map)
		free(data->map.map);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
}
