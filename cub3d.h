/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:51:12 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/09 18:56:57 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

// X11 Keysym
// https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h
# include <X11/keysym.h>

# include "libft.h"

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1080
# endif

typedef struct s_cub3d
{
	void	*mlx;
	void	*win;
}	t_cub3d;

// Utility functions
void	exit_error(char *err);

#endif
