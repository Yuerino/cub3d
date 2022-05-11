/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbienias <sbienias@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:54:12 by sbienias          #+#    #+#             */
/*   Updated: 2022/05/11 11:57:19 by sbienias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_char(t_cub3d *mlx, int dir)
{
	if (dir == UP)
		mlx->player.y -= 5;
	if (dir == DOWN)
		mlx->player.y += 5;
	if (dir == LEFT)
		mlx->player.x -= 5;
	if (dir == RIGHT)
		mlx->player.x += 5;
	draw(mlx);
	return ;
}

int	catch_key(int key, t_cub3d *mlx)
{
	if (key == UP || key == LEFT || key == DOWN || key == RIGHT)
	{
		move_char(mlx, key);
	}
	else if (key == ESC)
		close_game(mlx);
	return (0);
}
