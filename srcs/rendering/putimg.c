/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putimg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:38:34 by sbienias          #+#    #+#             */
/*   Updated: 2022/05/12 06:32:53 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @note This function can be extracted to somewhere else
 * @brief Draw line from one point to another using DDA Algo
 * @param img_ptr Pointer of image to be drawn to
 * @param p1 Integer array size of 2 that has coordination of first point (x|y)
 * @param p2 Integer array size of 2 that has coordination of second point (x|y)
 * @param line_color Color of the line to be drawn
 */
void	draw_line(void *img_ptr, int p1[2], int p2[2], int line_color)
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

void	draw(t_cub3d *mlx)
{
	void	*minimap_rays_img;

	mlx->main_img = clear_image(mlx->main_img);
	minimap_rays_img = image_dup(mlx->mlx, mlx->minimap.img_ptr);
	draw_minimap_player(mlx, minimap_rays_img, 0, 0);
	cast_rays(mlx, minimap_rays_img);
	put_image_to_image(mlx->main_img, minimap_rays_img, \
		WIN_WIDTH - mlx->minimap.width, WIN_HEIGHT - mlx->minimap.height);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->main_img, 0, 0);
	mlx_destroy_image(mlx->mlx, minimap_rays_img);
}
