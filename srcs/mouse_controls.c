/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:15:19 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/12 09:18:40 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_cub3d *data)
{
	if (data->mouse_x < 0)
	{
		data->mouse_x = x;
		return (0);
	}
	if (abs(data->mouse_x - x) > 10)
	{
		if (x < data->mouse_x)
			move_camera(data, &data->player, XK_Left);
		else if (x > data->mouse_x)
			move_camera(data, &data->player, XK_Right);
		data->mouse_x = x;
	}
	if (x < WIN_WIDTH * 0.3 || x > WIN_WIDTH * 0.7)
	{
		mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		data->mouse_x = WIN_WIDTH / 2;
	}
	if (y < WIN_HEIGHT * 0.3 || y > WIN_HEIGHT * 0.7)
		mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}
