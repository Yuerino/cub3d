/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 00:11:37 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 01:02:00 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "libft.h"

typedef struct s_cub3d	t_cub3d;

void	exit_error(char *err, t_cub3d *data);
void	exit_perror(char *err, t_cub3d *data);
void	free_carray(char **array);

# endif
