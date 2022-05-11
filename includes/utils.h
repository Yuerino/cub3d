/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 00:11:37 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/11 17:39:44 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

typedef struct s_cub3d	t_cub3d;

void	*image_dup(void *mlx, void *img);
void	*clear_image(void *img);
void	put_image_to_image(void *dest, void *src, int x_offset, int y_offset);

int		is_color_valid(int *color);
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
