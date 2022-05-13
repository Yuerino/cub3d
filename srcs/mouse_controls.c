/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbienias <sbienias@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:15:19 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 09:48:05 by sbienias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_cub3d *data)
{
	const double	old_dir_x = data->player.dir_x;

	x = x / 2 + x - (WIN_WIDTH / 2);
	//x = x / 2 + x - (WIN_WIDTH / 2) - data->mouse_x;
	y = y / 2 + y - (WIN_WIDTH / 2);
	printf("%d x, %d data\n", x, data->mouse_x);
	// if (x > 50 || x < -50)
	// {
	// 	if (x > 10)
	// 	{
	// 		data->player.dir_x = data->player.dir_x * cos(-data->player.speed) 
	// 		-data->player.dir_y * sin(-data->player.speed);
	// 		data->player.dir_y = old_dir_x * sin(-data->player.speed) + 
	// 		data->player.dir_y * cos(-data->player.speed); 
	// 		draw(data);
	// 	}
	// 	else if (x < -10)
	// 	{
	// 		data->player.dir_x = data->player.dir_x * cos(data->player.speed) 
	// 		- data->player.dir_y * sin(data->player.speed);
	// 		data->player.dir_y = old_dir_x * sin(data->player.speed) + 
	// 		data->player.dir_y * cos(data->player.speed);
	// 		draw(data);
	// 	}
	// }
	if (data->mouse_x - x < 500 && data->mouse_x - x > -500 )
	{
		if (data->mouse_x - x > 3)
		{
			data->player.dir_x = data->player.dir_x * cos(-data->player.speed) \
			-data->player.dir_y * sin(-data->player.speed);
			data->player.dir_y = old_dir_x * sin(-data->player.speed) +
			data->player.dir_y * cos(-data->player.speed); 
			draw(data);
		}
		else if (data->mouse_x - x < -3)
		{
			data->player.dir_x = data->player.dir_x * cos(data->player.speed) \
			- data->player.dir_y * sin(data->player.speed);
			data->player.dir_y = old_dir_x * sin(data->player.speed) +
			data->player.dir_y * cos(data->player.speed);
			draw(data);
		}
	}
	data->mouse_x = x;
	// mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	// //data->mouse_x = data->mouse_x / 2 + data->mouse_x - (WIN_WIDTH / 2);
	// mlx_mouse_get_pos(data->mlx, data->win, &data->mouse_x, &y);
	// data->mouse_x = data->mouse_x / 2 + data->mouse_x - (WIN_WIDTH / 2);
	return (0);
}
