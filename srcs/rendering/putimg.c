/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putimg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:38:34 by sbienias          #+#    #+#             */
/*   Updated: 2022/05/16 16:03:12 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Chooses the color from within the specified texture based on the
 * x and y axis, darkens the pixels on the N and S sides
 * @return Color of the texture at (x|y)
 */
int	get_color_from_texture(t_ray ray, int x, int y)
{
	char	*addr;
	t_img	*texture_img;

	texture_img = (t_img *)(ray.wall_texture->img_ptr);
	addr = texture_img->data + (y % texture_img->height * \
		texture_img->size_line + x * (texture_img->bpp / 8));
	if (ray.wall_dir)
		return (*(unsigned int *)addr / 2 & 0b011111110111111101111111);
	return (*(unsigned int *)addr);
}

/**
 * @brief Find the y index of the texture depending on the line height
 * @param wall_y Current y-coordinate of the wall
 * @return y-coordinate of the texture
 */
int	find_texture_y(t_ray ray, int wall_y)
{
	int	wall_start_y;

	wall_start_y = -ray.wall_height / 2 + WIN_HEIGHT / 2;
	if (ray.wall_height > WIN_HEIGHT)
		wall_y -= wall_start_y;
	return ((int)roundf(1.0f * ray.wall_texture->height \
		/ ray.wall_height * wall_y));
}

/**
 * @brief Find the x index of the texture
 * from player position and ray direction
 * @return x-coordinate of the texture
 */
int	find_texture_x(t_ray ray, t_player player)
{
	double	result;
	double	distance;

	if (!ray.wall_dir)
	{
		distance = (ray.map_x - player.x + (1 - ray.step_x) / 2) / ray.dir_x;
		result = player.y + distance * ray.dir_y;
	}
	else
	{
		distance = (ray.map_y - player.y + (1 - ray.step_y) / 2) / ray.dir_y;
		result = player.x + distance * ray.dir_x;
	}
	result -= floor(result);
	result = (int)(result * 64);
	if ((ray.wall_dir && ray.dir_y < 0)
		|| (!ray.wall_dir && ray.dir_x > 0))
		result = ray.wall_texture->width - result - 1;
	return (result);
}

/**
 * @brief Determine the texture to use depending on the
 * side of the ray hit and wall-player relation
 */
void	choose_texture(t_cub3d *data, t_ray *ray)
{
	if (ray->wall_dir == 0)
	{
		if (data->player.x - ray->map_x < 0)
			ray->wall_texture = &data->map.west;
		else
			ray->wall_texture = &data->map.east;
	}
	else
	{
		if (data->player.y - ray->map_y < 0)
			ray->wall_texture = &data->map.north;
		else
			ray->wall_texture = &data->map.south;
	}
}

/**
 * @brief Render a full screen frame including minimap
 */
void	draw(t_cub3d *mlx)
{
	void	*minimap_img_ptr;

	mlx->main_img = clear_image(mlx->main_img);
	minimap_img_ptr = image_dup(mlx->mlx, mlx->minimap.img_ptr);
	draw_minimap_player(mlx, minimap_img_ptr, 0, 0);
	cast_rays(mlx, minimap_img_ptr);
	put_image_to_image(mlx->main_img, minimap_img_ptr, \
		WIN_WIDTH - mlx->minimap.width, WIN_HEIGHT - mlx->minimap.height);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->main_img, 0, 0);
	mlx_destroy_image(mlx->mlx, minimap_img_ptr);
}
