/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:27:49 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 04:07:01 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLER_H
# define INPUT_HANDLER_H

typedef struct s_cub3d	t_cub3d;
typedef struct s_map	t_map;

void	init_cub3d(t_cub3d *data, char *filename);
void	read_file_data(t_cub3d *data, char *filename);
int		read_map(t_cub3d *data, char *line, int fd);
int		validate_map(t_map *map);

void	free_data(t_cub3d *data);

#endif
