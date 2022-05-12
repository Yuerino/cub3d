/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbienias <sbienias@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:15:19 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/12 14:15:18 by sbienias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_cub3d *data)
{
	const double	old_dir_x = data->player.dir_x;

	x = x / 2 + x - (WIN_WIDTH / 2);
	y = y / 2 + y - (WIN_WIDTH / 2);
	if (data->mouse_x - x < 100 && data->mouse_x - x > -100 )
	{
		if (data->mouse_x - x > 5)
		{
			data->player.dir_x = data->player.dir_x * cos(-data->player.speed) \
			-data->player.dir_y * sin(-data->player.speed) * 0.95;
			data->player.dir_y = old_dir_x * sin(-data->player.speed) + \
			data->player.dir_y * cos(-data->player.speed) * 0.95; 
		}
		else if (data->mouse_x - x < -5)
		{
			data->player.dir_x = data->player.dir_x * cos(data->player.speed) \
			- data->player.dir_y * sin(data->player.speed) * 0.95;
			data->player.dir_y = old_dir_x * sin(data->player.speed) + \
			data->player.dir_y * cos(data->player.speed) * 0.95;
		}
		else
		{
			data->mouse_x = x;
			return (0);
		}
		draw(data);
	}
	data->mouse_x = x;
	return (0);
}
