/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:11:53 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 08:18:36 by cthien-h         ###   ########.fr       */
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
 * @brief Calculate the wall height
 * and where the wall starts and ends on vertical line (y)
 */
static void	calc_wall_height(t_ray *ray)
{
	int	line_height;

	line_height = (int)fabs(WIN_HEIGHT / ray->distance);
	ray->wall_y[0] = -line_height / 2 + WIN_HEIGHT / 2;
	ray->wall_y[1] = line_height / 2 + WIN_HEIGHT / 2;
	if (ray->wall_y[0] < 0)
		ray->wall_y[0] = 0;
	if (ray->wall_y[1] >= WIN_HEIGHT)
		ray->wall_y[1] = WIN_HEIGHT - 1;
}

/**
 * @todo add texture for wall instead of fixed color
 * @brief Draw a vertical line on screen with ceiling, floor and wall
 * @param x Current vertical stripe (x-coordinate) of the screen
 */
static void	draw_vertical_line(t_cub3d *data, t_ray ray, int x)
{
	int	color;
	int	y;

	color = 0x0000FF;
	if (ray.wall_dir)
		color = color / 2;
	y = 0;
	while (y <= WIN_HEIGHT)
	{
		if (y >= ray.wall_y[0] && y <= ray.wall_y[1])
			ft_mlx_pixel_put(data->main_img, x, y, color);
		else if (y < ray.wall_y[0])
			ft_mlx_pixel_put(data->main_img, x, y, data->map.floor_color);
		else if (y > ray.wall_y[1])
			ft_mlx_pixel_put(data->main_img, x, y, data->map.ceiling_color);
		y++;
	}
}

/**
 * @brief Cast all vertical stripe rays
 * and draw vertical lines and rays for minimap accordingly
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
		ray.distance = ray.distance * \
			cos(atan2(data->player.dir_y, data->player.dir_x) - ray.angle);
		calc_wall_height(&ray);
		draw_vertical_line(data, ray, x);
		x++;
	}
}
