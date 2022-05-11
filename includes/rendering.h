/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbienias <sbienias@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:27:49 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/11 12:01:49 by sbienias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

#  define UP 119
#  define DOWN 115
#  define LEFT 97
#  define RIGHT 100
#  define ESC 65307

typedef struct s_cub3d	t_cub3d;

void	draw(t_cub3d *mlx);
int		catch_key(int key, t_cub3d *mlx);

#endif
