/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:27:49 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 06:49:02 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLER_H
# define INPUT_HANDLER_H

typedef struct s_cub3d	t_cub3d;
typedef struct s_map	t_map;
typedef struct s_image	t_image;

void	init_cub3d(t_cub3d *data, char *filename);
void	read_file_data(t_cub3d *data, char *filename);
int		get_texture(t_cub3d *data, char *line, t_image *texture);
int		read_map(t_cub3d *data, char *line, int fd);
int		validate_map(t_map *map);

int		print_read_error(t_cub3d *data, char *err, char *perr, char **arr);
void	free_data(t_cub3d *data);

#endif
