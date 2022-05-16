/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:07:38 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/16 16:00:50 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @note right now put square mainly for minimap so I leave it here
 * @brief Draw a square to the image
 * @param img_ptr Pointer of image to be drawn to
 * @param point Starting point of the square (x|y)
 * @param color Color of the square (filled)
 * @param square_size Size of the square
 */
void	put_square(void *img_ptr, int point[2], int color, int square_size)
{
	int	x;
	int	y;

	y = 0;
	while (y < square_size)
	{
		x = 0;
		while (x < square_size)
		{
			ft_mlx_pixel_put(img_ptr, (point[0] * square_size) + x, \
				(point[1] * square_size) + y, color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Draw line from one point to another using DDA Algo
 * @param img_ptr Pointer of image to be drawn to
 * @param p1 Integer array size of 2 that has coordination of first point (x|y)
 * @param p2 Integer array size of 2 that has coordination of second point (x|y)
 * @param line_color Color of the line to be drawn
 */
static void	draw_line(void *img_ptr, int p1[2], int p2[2], int line_color)
{
	double	x;
	double	y;
	double	delta_x;
	double	delta_y;
	int		steps;

	x = p1[0];
	y = p1[1];
	delta_x = p2[0] - p1[0];
	delta_y = p2[1] - p1[1];
	if ((int)fabs(delta_x) > (int)fabs(delta_y))
		steps = (int)fabs(delta_x);
	else
		steps = (int)fabs(delta_y);
	delta_x /= steps;
	delta_y /= steps;
	while (steps > 0)
	{
		ft_mlx_pixel_put(img_ptr, round(x), round(y), line_color);
		x += delta_x;
		y += delta_y;
		steps--;
	}
}

/**
 * @brief Create and draw the base minimap without player to
 * minimap struct
 */
void	create_minimap(t_cub3d *data)
{
	int		point[2];
	int		color;
	int		square_size;

	square_size = data->minimap.height / data->map.height;
	point[1] = 0;
	while (data->map.data[point[1]])
	{
		point[0] = 0;
		while (data->map.data[point[1]][point[0]])
		{
			color = 0x33aaaa;
			if (data->map.data[point[1]][point[0]] == '1')
				color = 0xffffff;
			if (data->map.data[point[1]][point[0]] != ' ')
				put_square(data->minimap.img_ptr, point, color, square_size);
			point[0]++;
		}
		point[1]++;
	}
}

/**
 * @brief Draw a red circle represent a minimap player to the image
 * @param img Image pointer of the minimap
 * @param x_offset x start point of the minimap
 * @param y_offset y start point of the minimap
 */
void	draw_minimap_player(t_cub3d *data, void *img,
	int x_offset, int y_offset)
{
	int	radius;
	int	square_size;
	int	y;
	int	x;

	square_size = data->minimap.height / data->map.height;
	radius = (int)(square_size / 5);
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				ft_mlx_pixel_put(img, \
					(data->player.x * square_size + x) + x_offset, \
					(data->player.y * square_size + y) + y_offset, 0xff0000);
			x++;
		}
		y++;
	}
}

/**
 * @brief Draw a ray from player to the wall on the minimap
 * @param minimap_rays_img Image pointer of the minimap
 * @param color Color of the ray
 */
void	draw_minimap_ray(t_cub3d *data, t_ray ray,
	void *minimap_rays_img, int color)
{
	int	p1[2];
	int	p2[2];
	int	square_size;

	square_size = data->minimap.height / data->map.height;
	p1[0] = (int)(data->player.x * square_size);
	p1[1] = (int)(data->player.y * square_size);
	p2[0] = (int)((data->player.x - ray.distance * cos(ray.angle)) * \
		square_size);
	p2[1] = (int)((data->player.y - ray.distance * sin(ray.angle)) * \
		square_size);
	draw_line(minimap_rays_img, p1, p2, color);
}
