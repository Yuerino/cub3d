/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:11:53 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/16 16:02:30 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculate all the necessary magic to trace a ray using DDA algo
 */
static void	prep_ray(t_cub3d *data, t_ray *ray)
{
	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	if (ray->dir_x > 0)
	{
		ray->step_x = -1;
		ray->current_x = (data->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->current_x = (ray->map_x + 1.0 - data->player.x) * ray->delta_x;
	}
	if (ray->dir_y > 0)
	{
		ray->step_y = -1;
		ray->current_y = (data->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->current_y = (ray->map_y + 1.0 - data->player.y) * ray->delta_y;
	}
}

/**
 * @brief Cast the ray using DDA algo until it hits a wall
 * then calculate and set the distance it travels
 */
static void	cast_ray(t_cub3d *data, t_ray *ray)
{
	while (data->map.data[ray->map_y][ray->map_x] != '1')
	{
		if (ray->current_x < ray->current_y)
		{
			ray->current_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->wall_dir = 0;
		}
		else
		{
			ray->current_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->wall_dir = 1;
		}
	}
	if (!ray->wall_dir)
		ray->distance = fabs((ray->map_x - data->player.x + \
			(1 - ray->step_x) / 2) / ray->dir_x);
	else
		ray->distance = fabs((ray->map_y - data->player.y + \
			(1 - ray->step_y) / 2) / ray->dir_y);
}

/**
 * @brief Calculate the wall height
 * and where the wall starts and ends on vertical line (y)
 */
static void	calc_wall_height(t_ray *ray)
{
	ray->wall_height = (int)fabs(WIN_HEIGHT / ray->distance);
	ray->wall_y[0] = -ray->wall_height / 2 + WIN_HEIGHT / 2;
	ray->wall_y[1] = ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (ray->wall_y[0] < 0)
		ray->wall_y[0] = 0;
	if (ray->wall_y[1] >= WIN_HEIGHT)
		ray->wall_y[1] = WIN_HEIGHT - 1;
}

/**
 * @brief Calculate wall height based on ray length and draw it
 * to main image
 * @param x Current vertical stripe (x-coordinate) of the screen
 */
static void	draw_vertical_line(t_cub3d *data, t_ray ray, int x)
{
	int	y;
	int	wall_y;
	int	texture_x;
	int	texture_color;

	choose_texture(data, &ray);
	texture_x = find_texture_x(ray, data->player);
	wall_y = 0;
	y = 0;
	while (y <= WIN_HEIGHT)
	{
		if (y >= ray.wall_y[0] && y <= ray.wall_y[1])
		{
			texture_color = get_color_from_texture(ray, texture_x, \
				find_texture_y(ray, wall_y++));
			ft_mlx_pixel_put(data->main_img, x, y, texture_color);
		}
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
		ray.dir_x = cos(ray.angle);
		ray.dir_y = sin(ray.angle);
		prep_ray(data, &ray);
		cast_ray(data, &ray);
		draw_minimap_ray(data, ray, minimap_rays_img, 0xFF0000);
		ray.distance = ray.distance * \
			cos(atan2(data->player.dir_y, data->player.dir_x) - ray.angle);
		calc_wall_height(&ray);
		draw_vertical_line(data, ray, x);
		x++;
	}
}
