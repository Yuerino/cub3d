/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:11:53 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/14 16:54:24 by cthien-h         ###   ########.fr       */
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
	ray->x_offset = current_x;
	ray->y_offset = current_y;
}

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
	double	result = 0;
	double	distance = 0;
	// double test = player.y - ray.map_y / sin(ray.angle);

	// if (ray.wall_dir == 1)
	// {
	// 	result = player.y - ray.map_y - (cos(ray.angle) * ray.distance);
	// 	printf("test map y %d player %f offset %f the prev pme %f\n", ray.map_y, player.y, (cos(ray.angle) * ray.distance), ray.y_offset);

	// }
	// else
	// {
	// 	result = player.x - ray.map_x - (sin(ray.angle) * ray.distance);
	// 	printf("test map x %d player %f offset %f the prev pme %f\n", ray.map_x, player.x, (sin(ray.angle) * ray.distance), ray.x_offset);
	// }

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

	// result = (ray.map_x + ray.map_y);
	// if (ray.wall_dir == 0)
	// 	result = (sin(ray.angle) * distance);
	// else
	// 	result = (cos(ray.angle) * distance);
	// if (result < 0)
	// 	result *= -1;
	// (void)player;

	// result = (result * 64);
	// return ((int)result % 64);
}

/**
 * @brief Determine the texture to use depending on the
 * side of the ray hit and wall-player relation
 */
t_image	choose_texture(t_cub3d *data, t_ray ray)
{
	t_image texture;

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

/**
 * @todo fix texture display
 * @brief Calculate wall height based on ray length and draw it
 * to main image
 * @param x Current vertical stripe (x-coordinate) of the screen
 */
void	draw_wall(t_cub3d *data, t_ray ray, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	int	textx;
	int i = 0;
	t_image	texture;

	texture = choose_texture(data, ray);
	ray.distance = ray.distance * \
		cos(atan2(data->player.dir_y, data->player.dir_x) - ray.angle);
	line_height = (int)fabs(WIN_HEIGHT / ray.distance);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	//steps = 1.0 * data->map.north.height / (draw_end - draw_start);
	//steps = data->map.north.height / (draw_end - draw_start);
	textx = find_x(ray, data->player);
	while (draw_start <= draw_end)
	{
		color = get_color_from_texture(texture, textx, \
		find_y(ray, line_height, i++), ray);
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
