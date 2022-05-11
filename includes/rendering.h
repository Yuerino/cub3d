/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:27:49 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/11 19:15:54 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

typedef struct s_cub3d	t_cub3d;
typedef struct s_image	t_image;

void	draw(t_cub3d *mlx);
void	create_minimap(t_cub3d *data);
void	draw_minimap(t_cub3d *data);
void	put_square(void *img_ptr, int point[2], int color, int square_size);
void	draw_player(t_cub3d *mlx, int x_offset, int y_offset);

#endif
