/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:50:13 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/09 18:57:17 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	data;

	(void)argv;
	if (argc != 2)
		exit_error("Usage: ./cub3d [map file]");
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_loop(data.mlx);
	return (0);
}
