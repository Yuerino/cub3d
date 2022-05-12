/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:35:33 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/12 08:37:16 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

// X11 Keysym
// https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h
# include <X11/keysym.h>

typedef struct s_cub3d	t_cub3d;
typedef struct s_player	t_player;

int		close_game(t_cub3d *data);
void	move_camera(t_cub3d *data, t_player *p, int key);

int		catch_key(int key, t_cub3d *mlx);
int		mouse_move(int x, int y, t_cub3d *data);

#endif
