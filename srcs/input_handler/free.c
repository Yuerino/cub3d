/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 06:32:37 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 07:12:50 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Free all allocated data inside map struct if possible
 */
static void	free_map(t_map *map, void *mlx)
{
	if (map->north.img_ptr)
		mlx_destroy_image(mlx, map->north.img_ptr);
	if (map->north.filename)
		free(map->north.filename);
	if (map->south.img_ptr)
		mlx_destroy_image(mlx, map->south.img_ptr);
	if (map->south.filename)
		free(map->south.filename);
	if (map->west.img_ptr)
		mlx_destroy_image(mlx, map->west.img_ptr);
	if (map->west.filename)
		free(map->west.filename);
	if (map->east.img_ptr)
		mlx_destroy_image(mlx, map->east.img_ptr);
	if (map->east.filename)
		free(map->east.filename);
	if (map->data)
		free_carray(map->data);
}

/**
 * @brief Free all allocated data inside data struct including those from mlx
 */
void	free_data(t_cub3d *data)
{
	free_map(&data->map, data->mlx);
	if (data->main_img)
		mlx_destroy_image(data->mlx, data->main_img);
	if (data->minimap.img_ptr)
		mlx_destroy_image(data->mlx, data->minimap.img_ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
