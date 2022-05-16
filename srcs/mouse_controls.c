/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:15:19 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/16 17:08:57 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Function hooked on mouse move event, to rotate player facing direction
 * with mouse
 */
int	mouse_move(int x, int y, t_cub3d *data)
{
	if (x < WIN_WIDTH * 0.3 || x > WIN_WIDTH * 0.7)
	{
		mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		data->mouse_x = WIN_WIDTH / 2;
		return (0);
	}
	if (y < WIN_HEIGHT * 0.3 || y > WIN_HEIGHT * 0.7)
	{
		mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		return (0);
	}
	x = x / 2 + x - (WIN_WIDTH / 2);
	y = y / 2 + y - (WIN_HEIGHT / 2);
	if (data->mouse_x - x < 500 && data->mouse_x - x > -500)
	{
		if (data->mouse_x - x > 5)
			move_camera(data, &data->player, XK_Left);
		else if (data->mouse_x - x < -5)
			move_camera(data, &data->player, XK_Right);
	}
	data->mouse_x = x;
	return (0);
}
