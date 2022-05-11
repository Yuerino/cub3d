/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:07:38 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/11 19:08:34 by cthien-h         ###   ########.fr       */
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
 * @brief Draw a minimap with player directly to the main image
 */
void	draw_minimap(t_cub3d *data)
{
	put_image_to_image(data->main_img, data->minimap.img_ptr, \
		WIN_WIDTH - data->minimap.width, WIN_HEIGHT - data->minimap.height);
	draw_player(data, WIN_WIDTH - data->minimap.width, \
		WIN_HEIGHT - data->minimap.height);
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
