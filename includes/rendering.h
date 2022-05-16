/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:27:49 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/16 16:02:21 by cthien-h         ###   ########.fr       */
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
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	delta_x;
	double	delta_y;
	double	current_x;
	double	current_y;
	int		wall_dir;
	double	distance;
	double	wall_y[2];
	int		wall_height;
	t_image	*wall_texture;
}	t_ray;

void	draw(t_cub3d *mlx);
void	cast_rays(t_cub3d *data, void *minimap_rays_img);

int		get_color_from_texture(t_ray ray, int x, int y);
int		find_texture_y(t_ray ray, int wall_y);
int		find_texture_x(t_ray ray, t_player player);
void	choose_texture(t_cub3d *data, t_ray *ray);

void	put_square(void *img_ptr, int point[2], int color, int square_size);
void	create_minimap(t_cub3d *data);
void	draw_minimap_player(t_cub3d *data, void *img,
			int x_offset, int y_offset);
void	draw_minimap_ray(t_cub3d *data, t_ray ray,
			void *minimap_rays_img, int color);

#endif
