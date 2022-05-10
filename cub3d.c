/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:50:13 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 00:19:34 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	data;

	if (argc != 2)
		exit_error("Usage: ./cub3d [map file]", NULL);
	init_cub3d(&data, argv[1]);
	mlx_loop(data.mlx);
	free_data(&data);
	return (0);
}
