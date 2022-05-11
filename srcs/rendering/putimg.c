/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putimg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:38:34 by sbienias          #+#    #+#             */
/*   Updated: 2022/05/11 19:09:33 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Draw a red circle represent a player to the minimap
 * @param x_offset x start point of the minimap
 * @param y_offset y start point of the minimap
 */
void	draw_player(t_cub3d *mlx, int x_offset, int y_offset)
{
	int	radius;
	int	square_size;
	int	y;
	int	x;

	radius = 10;
	square_size = mlx->minimap.height / mlx->map.height;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				ft_mlx_pixel_put(mlx->main_img, \
					(mlx->player.x * square_size + x) + x_offset, \
					(mlx->player.y * square_size + y) + y_offset, 0xff0000);
			x++;
		}
		y++;
	}
}

void	draw(t_cub3d *mlx)
{
	draw_minimap(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->main_img, 0, 0);
}
