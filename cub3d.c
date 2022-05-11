/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:50:13 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 23:40:57 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Free data and exit program
 * @note For development usage, delete or move it later
 */
static int	close_game(t_cub3d *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	data;

	if (argc != 2)
		exit_error("Usage: ./cub3d [map file]", NULL);
	init_cub3d(&data, argv[1]);
	mlx_hook(data.win, 17, 0, close_game, &data);
	mlx_loop(data.mlx);
	return (0);
}
