/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 00:11:37 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 06:05:12 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

typedef struct s_cub3d	t_cub3d;

void	*image_dup(void *mlx, void *img);
void	*clear_image(void *img);
void	put_image_to_image(void *dest, void *src, int x_offset, int y_offset);

void	ft_mlx_pixel_put(void *img_ptr, int x, int y, int color);
void	ft_mlx_pixel_put_rgb(void *img_ptr, int x, int y, int rgb[3]);

int		is_color_valid(int color[3]);
int		str_rgb_to_color(char *r, char *g, char *b, long long *color);
int		is_ext_valid(char *filename, char *ext);
int		is_nbr(char *s);

int		print_error(char *err, t_cub3d *data);
int		print_perror(char *err, t_cub3d *data);
void	exit_error(char *err, t_cub3d *data);
void	exit_perror(char *err, t_cub3d *data);

void	free_carray(char **array);
int		carray_len(char **array);
char	**carray_expand(char **array);

#endif
