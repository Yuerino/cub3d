/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:50:13 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 15:29:17 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Function hooked into expose event
 * @note everything window is resized, it just clear the image
 * so we redraw the image here (not rendering)
 */
static int	redraw(t_cub3d *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->main_img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	data;

	if (argc != 2)
		exit_error("Usage: ./cub3d [map file]", NULL);
	init_cub3d(&data, argv[1]);
	mlx_hook(data.win, 17, 0, close_game, &data);
	mlx_key_hook(data.win, catch_key, &data);
	mlx_expose_hook(data.win, redraw, &data);
	mlx_mouse_hide(data.mlx, data.win);
	mlx_hook(data.win, 6, (1L << 6), mouse_move, &data);
	draw(&data);
	mlx_loop(data.mlx);
	return (0);
}
