/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbienias <sbienias@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:11:53 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/14 19:51:36 by sbienias         ###   ########.fr       */
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
	double	delta_x;
	double	delta_y;
	double	current_x;
	double	current_y;
	int		hit;

	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);

	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;

	delta_x = fabs(1 / ray->dir_x);
	delta_y = fabs(1 / ray->dir_y);

	if (ray->dir_x > 0)
	{
		ray->step_x = -1;
		current_x = (data->player.x - ray->map_x) * delta_x;
	}
	else
	{
		ray->step_x = 1;
		current_x = (ray->map_x + 1.0 - data->player.x) * delta_x;
	}
	if (ray->dir_y > 0)
	{
		ray->step_y = -1;
		current_y = (data->player.y - ray->map_y) * delta_y;
	}
	else
	{
		ray->step_y = 1;
		current_y = (ray->map_y + 1.0 - data->player.y) * delta_y;
	}

	hit = 0;
	while (!hit)
	{
		if (current_x < current_y)
		{
			current_x += delta_x;
			ray->map_x += ray->step_x;
			ray->wall_dir = 0;
		}
		else
		{
			current_y += delta_y;
			ray->map_y += ray->step_y;
			ray->wall_dir = 1;
		}
		if (data->map.data[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (!ray->wall_dir)
		ray->distance = fabs((ray->map_x - data->player.x + \
			(1 - ray->step_x) / 2) / ray->dir_x);
	else
		ray->distance = fabs((ray->map_y - data->player.y + \
			(1 - ray->step_y) / 2) / ray->dir_y);
}

/**
 * @brief Calculate wall height based on ray length and draw it
 * to main image
 * @param x Current vertical stripe (x-coordinate) of the screen
 */
void	draw_wall(t_cub3d *data, t_ray ray, int x)
{
	int		line_height;
	int		draw_ends[2];
	int		color;
	int		texture_x;
	t_image	texture;

	texture = choose_texture(data, ray);
	ray.distance = ray.distance * \
		cos(atan2(data->player.dir_y, data->player.dir_x) - ray.angle);
	line_height = (int)fabs(WIN_HEIGHT / ray.distance);
	draw_ends[0] = -line_height / 2 + WIN_HEIGHT / 2;
	draw_ends[1] = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_ends[0] < 0)
		draw_ends[0] = 0;
	if (draw_ends[1] >= WIN_HEIGHT)
		draw_ends[1] = WIN_HEIGHT - 1;
	texture_x = find_x(ray, data->player);
	while (draw_ends[0] <= draw_ends[1])
	{
		color = get_color_from_texture(texture, texture_x, \
		find_y(ray, line_height, draw_ends[0]), ray);
		ft_mlx_pixel_put(data->main_img, x, draw_ends[0], color);
		draw_ends[0]++;
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
