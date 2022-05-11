/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:37:00 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/11 15:48:09 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Free data and exit program
 */
int	close_game(t_cub3d *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * @brief Move player sideways (strafing) if there's no collsion
 */
static void	move_player_sideways(t_map *map, t_player *p, int key)
{
	if (key == XK_a)
	{
		if (map->data[(int)p->y][(int)(p->x - p->dir_y * p->speed)] == '0')
			p->x -= p->dir_y * p->speed;
		if (map->data[(int)(p->y + p->dir_x * p->speed)][(int)p->x] == '0')
			p->y += p->dir_x * p->speed;
	}
	else if (key == XK_d)
	{
		if (map->data[(int)p->y][(int)(p->x + p->dir_y * p->speed)] == '0')
			p->x += p->dir_y * p->speed;
		if (map->data[(int)(p->y - p->dir_x * p->speed)][(int)p->x] == '0')
			p->y -= p->dir_x * p->speed;
	}
}

/**
 * @brief Move the player if there's no collision
 */
static void	move_player(t_cub3d *data, t_map *map, t_player *p, int key)
{
	if (key == XK_w)
	{
		if (map->data[(int)p->y][(int)(p->x - p->dir_x * p->speed)] == '0')
			p->x -= p->dir_x * p->speed;
		if (map->data[(int)(p->y - p->dir_y * p->speed)][(int)p->x] == '0')
			p->y -= p->dir_y * p->speed;
	}
	else if (key == XK_s)
	{
		if (map->data[(int)p->y][(int)(p->x + p->dir_x * p->speed)] == '0')
			p->x += p->dir_x * p->speed;
		if (map->data[(int)(p->y + p->dir_y * p->speed)][(int)p->x] == '0')
			p->y += p->dir_y * p->speed;
	}
	else
		move_player_sideways(map, p, key);
	draw(data);
}

/**
 * @brief Rotate player facing direction
 * @note 2D rotation matrix formula here:
 * https://en.wikipedia.org/wiki/Rotation_matrix
 */
static void	move_camera(t_cub3d *data, t_player *p, int key)
{
	double	old_dir_x;

	old_dir_x = p->dir_x;
	if (key == XK_Left)
	{
		p->dir_x = p->dir_x * cos(-p->speed) - p->dir_y * sin(-p->speed);
		p->dir_y = old_dir_x * sin(-p->speed) + p->dir_y * cos(-p->speed);
	}
	else if (key == XK_Right)
	{
		p->dir_x = p->dir_x * cos(p->speed) - p->dir_y * sin(p->speed);
		p->dir_y = old_dir_x * sin(p->speed) + p->dir_y * cos(p->speed);
	}
	draw(data);
}

/**
 * @brief Event function on key pressed, to be used with mlx_key_hook
 */
int	catch_key(int key, t_cub3d *mlx)
{
	if (key == XK_w || key == XK_s || key == XK_a || key == XK_d)
		move_player(mlx, &mlx->map, &mlx->player, key);
	else if (key == XK_Left || key == XK_Right)
		move_camera(mlx, &mlx->player, key);
	else if (key == XK_Escape)
		close_game(mlx);
	return (0);
}
