/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbienias <sbienias@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:27:49 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 10:38:48 by sbienias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# ifndef FOV
#  define FOV 60
# endif

typedef struct s_cub3d	t_cub3d;
typedef struct s_image	t_image;

typedef struct s_ray
{
	double	angle;
	int		map_x;
	int		map_y;
	int		wall_dir;
	double	distance;
	double	x_offset;
	double	y_offset;
}	t_ray;

void	draw(t_cub3d *mlx);
void	cast_rays(t_cub3d *data, void *minimap_rays_img);

void	draw_line(void *img_ptr, int p1[2], int p2[2], int line_color);
void	put_square(void *img_ptr, int point[2], int color, int square_size);
void	create_minimap(t_cub3d *data);
void	draw_minimap_player(t_cub3d *data, void *img,
			int x_offset, int y_offset);
void	draw_minimap_ray(t_cub3d *data, t_ray ray,
			void *minimap_rays_img, int color);

#endif
