/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:11:53 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/12 07:56:08 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @note black magic in here, not norm ofc, need refactor
 * DDA Algo to cast the ray, but the math to get step_x step_y
 * current_x current_y based on ray direction are magic for me
 */
static void	cast_single_ray(t_cub3d *data, t_ray *ray)
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	current_x;
	double	current_y;
	int		hit;

	ray_dir_x = cos(ray->angle);
	ray_dir_y = sin(ray->angle);

	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;

	delta_x = fabs(1 / ray_dir_x);
	delta_y = fabs(1 / ray_dir_y);

	if (ray_dir_x > 0)
	{
		step_x = -1;
		current_x = (data->player.x - ray->map_x) * delta_x;
	}
	else
	{
		step_x = 1;
		current_x = (ray->map_x + 1.0 - data->player.x) * delta_x;
	}
	if (ray_dir_y > 0)
	{
		step_y = -1;
		current_y = (data->player.y - ray->map_y) * delta_y;
	}
	else
	{
		step_y = 1;
		current_y = (ray->map_y + 1.0 - data->player.y) * delta_y;
	}

	hit = 0;
	while (!hit)
	{
		if (current_x < current_y)
		{
			current_x += delta_x;
			ray->map_x += step_x;
			ray->wall_dir = 0;
		}
		else
		{
			current_y += delta_y;
			ray->map_y += step_y;
			ray->wall_dir = 1;
		}
		if (data->map.data[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}

	if (!ray->wall_dir)
		ray->distance = fabs((ray->map_x - data->player.x + \
			(1 - step_x) / 2) / ray_dir_x);
	else
		ray->distance = fabs((ray->map_y - data->player.y + \
			(1 - step_y) / 2) / ray_dir_y);
}

/**
 * @todo add texture for wall instead of fixed color
 * @brief Calculate wall height based on ray length and draw it
 * to main image
 * @param x Current vertical stripe (x-coordinate) of the screen
 */
static void	draw_wall(t_cub3d *data, t_ray ray, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;

	line_height = (int)fabs(WIN_HEIGHT / ray.distance);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	if (data->map.data[ray.map_y][ray.map_x] == '1')
		color = 0xFF0000;
	else
		color = 0xFFFF00;
	if (ray.wall_dir)
		color = color / 2;
	while (draw_start <= draw_end)
	{
		ft_mlx_pixel_put(data->main_img, x, draw_start, color);
		draw_start++;
	}
}

/**
 * @brief Cast all vertical stripe rays
 * and draw the wall and rays for minimap accordingly
 * @param minimap_rays_img Image pointer of the minimap
 */
void	cast_rays(t_cub3d *data, void *minimap_rays_img)
{
	int		x;
	double	initial_angle;
	double	angle_step;
	t_ray	ray;

	initial_angle = atan2(data->player.dir_y, data->player.dir_x) \
		- (0.5 * (double)FOV / 180) * M_PI;
	angle_step = ((double)FOV / WIN_WIDTH / 180) * M_PI;
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray.angle = initial_angle + (angle_step * x);
		if (ray.angle < 0.0f)
			ray.angle = (M_PI * 2) + ray.angle;
		cast_single_ray(data, &ray);
		draw_minimap_ray(data, ray, minimap_rays_img, 0xFF0000);
		draw_wall(data, ray, x);
		x++;
	}
}
