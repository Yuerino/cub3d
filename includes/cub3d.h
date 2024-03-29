/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:51:12 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/15 17:48:13 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <mlx_int.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "input_handler.h"
# include "utils.h"
# include "controls.h"
# include "rendering.h"

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1080
# endif

typedef struct s_image
{
	void	*img_ptr;
	int		width;
	int		height;
	char	*filename;
}	t_image;

typedef struct s_map
{
	t_image		north;
	t_image		south;
	t_image		west;
	t_image		east;
	long long	floor_color;
	long long	ceiling_color;
	char		**data;
	int			height;
	int			max_width;
}	t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		speed;
}	t_player;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	void		*main_img;
	t_map		map;
	t_player	player;
	t_image		minimap;
	int			mouse_x;
}	t_cub3d;

#endif
