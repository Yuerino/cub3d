/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbienias <sbienias@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:51:13 by sbienias          #+#    #+#             */
/*   Updated: 2022/05/14 19:52:23 by sbienias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <mlx_int.h>
#include "cub3d.h"

/**
 * @brief Chooses the color from within the specified texture based on the
 * x and y axis, darkens the pixels on the N and S sides
 */
int	get_color_from_texture(t_image texture, int x, int y, t_ray ray)
{
	char	*adr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_img	*img;

	img = (t_img *)(texture.img_ptr);
	adr = mlx_get_data_addr(img, &bits_per_pixel, \
	&line_length, &endian);
	adr = adr + (y % img->height * line_length + x * (bits_per_pixel / 8));
	if (ray.wall_dir)
		return (*(unsigned int *)adr / 2 & 0b011111110111111101111111);
	return (*(unsigned int *)adr);
}

/**
 * @brief Decide the y index from the texture depending on the line
 * height and the current element
 */
int	find_y(t_ray ray, int distance, int index)
{
	int	result;
	int	draw_start;

	draw_start = -distance / 2 + WIN_HEIGHT / 2;
	if (distance > WIN_HEIGHT)
	{
		index -= draw_start;
	}
	if (draw_start > 0)
		index = index - draw_start;
	if (ray.wall_dir == 0)
		result = distance % 64;
	else
		result = (int)cos(ray.angle) % 64;
	result = roundf(64.0 / distance * index);
	return (result);
}

/**
 * @todo Make it not slide
 * @brief Decide the x index from the texture ray angle,
 * player's and the map tile hit position
 */
double	find_x(t_ray ray, t_player player)
{
	double	result;
	double	distance;

	if (!ray.wall_dir)
		distance = (ray.map_x - player.x + (1 - ray.step_x) / 2) / ray.dir_x;
	else
		distance = (ray.map_y - player.y + (1 - ray.step_y) / 2) / ray.dir_y;
	if (ray.wall_dir)
		result = player.x + distance * cos(ray.angle);
	else
		result = player.y + distance * sin(ray.angle);
	result -= floor(result);
	result = (int)(result * 64);
	if ((ray.wall_dir && sin(ray.angle) < 0)
		|| (!ray.wall_dir && cos(ray.angle) > 0))
		result = 64 - result - 1;
	return (result);
}

/**
 * @brief Determine the texture to use depending on the
 * side of the ray hit and wall-player relation
 */
t_image	choose_texture(t_cub3d *data, t_ray ray)
{
	t_image	texture;

	if (ray.wall_dir == 0)
	{
		if (data->player.x - ray.map_x < 0)
			texture = data->map.west;
		else
			texture = data->map.east;
	}
	else
	{
		if (data->player.y - ray.map_y < 0)
			texture = data->map.north;
		else
			texture = data->map.south;
	}
	return (texture);
}
