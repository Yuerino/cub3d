/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:50:13 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/12 04:59:36 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Debug function to print all data in struct
 * @note Development usage only, delete when submit
 */
// static void	print_data(t_cub3d *data)
// {
// 	// mlx_put_image_to_window(data->mlx, data->win, data->map.north.img_ptr, 0, 0);
// 	// mlx_put_image_to_window(data->mlx, data->win, data->map.south.img_ptr, data->map.north.width, 0);
// 	// mlx_put_image_to_window(data->mlx, data->win, data->map.west.img_ptr, 0, data->map.north.height);
// 	// mlx_put_image_to_window(data->mlx, data->win, data->map.east.img_ptr, data->map.west.width, data->map.south.height);
// 	printf("floor color: R: %d, G: %d, B: %d\n", data->map.floor_color[0], data->map.floor_color[1], data->map.floor_color[2]);
// 	printf("ceiling color: R: %d, G: %d, B: %d\n", data->map.ceiling_color[0], data->map.ceiling_color[1], data->map.ceiling_color[2]);
// 	printf("Player position: x: %f, y: %f, dir_x: %f, dir_y: %f\n", data->player.x, data->player.y, data->player.dir_x, data->player.dir_y);
// 	printf("Map height: %d, map data:\n", data->map.height);
// 	for (int i=0;data->map.data[i];i++)
// 	{
// 		printf("%s\n", data->map.data[i]);
// 	}
// }

/**
 * @brief Test image_dup function by duplicating north wall texture image
 * and put it in middle of the window
 * @note Development usage only, delete when submit
 */
// static void	image_dup_test(t_cub3d *data)
// {
// 	void	*new_img;

// 	new_img = image_dup(data->mlx, data->map.north.img_ptr);
// 	mlx_destroy_image(data->mlx, data->map.north.img_ptr);
// 	data->map.north.img_ptr = NULL;
// 	mlx_put_image_to_window(data->mlx, data->win, new_img, WIN_WIDTH / 2, WIN_HEIGHT / 2);
// 	mlx_destroy_image(data->mlx, new_img);
// }

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
	// print_data(&data);
	draw(&data);
	// image_dup_test(&data);
	mlx_hook(data.win, 17, 0, close_game, &data);
	mlx_key_hook(data.win, catch_key, &data);
	mlx_expose_hook(data.win, redraw, &data);
	mlx_loop(data.mlx);
	return (0);
}
