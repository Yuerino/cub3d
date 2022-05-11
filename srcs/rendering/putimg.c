/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putimg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbienias <sbienias@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:38:34 by sbienias          #+#    #+#             */
/*   Updated: 2022/05/11 11:26:45 by sbienias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;
	char	*adr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	adr = mlx_get_data_addr(data->img_ptr, &bits_per_pixel, \
	&line_length, &endian);
	dst = adr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_square(char type, t_cub3d *mlx, int x, int y)
{
	int	counter;
	int	i;
	int	storeCoord;
	int	color;

	color = 0x33aaaa;
	if (type == '1')
		color = 0xffffff;
	else if (type == ' ')
		return ;
	counter = 0;
	storeCoord = y;
	while (counter < 30)
	{
		i = 0;
		y = storeCoord;
		while (i < 30)
		{
			ft_mlx_pixel_put(&(mlx->img), x, y, color);
			y++;
			i++;
		}
		x++;
		counter++;
	}
}

void	draw_player(t_cub3d *mlx)
{
	int	radius;
	int	y;
	int	x;

	radius = 10;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				ft_mlx_pixel_put(&(mlx->img), mlx->player.x * 15 + x, \
				mlx->player.y * 15 + y, 0xff0000);
			x++;
		}
		y++;
	}
	// for (int x = 0; x < WIDTH; x++)
    // {
    //   //calculate ray position and direction
	// 	double cameraX = 2 * x / double(WIDTH) - 1; //x-coordinate in camera space
	// 	double rayDirX = mlx->dir_x + mlx->planeX * cameraX;
	// 	double rayDirY = mlx->dir_y + mlx->planeY * cameraX;
	// }
	// int	startingX =  mlx->player_X - 15 / 31;
	// int	startingY =  mlx->player_Y - 15 / 31;
}

void	draw(t_cub3d *mlx)
{
	int		coords[2];
	int		counter;
	int		i;
	char	**data;

	data = mlx->map.data;
	counter = -1;
	coords[0] = 0;
	coords[1] = 0;
	mlx->img.img_ptr = mlx_new_image(mlx->mlx, WIN_HEIGHT, WIN_WIDTH);
	while (data[++counter])
	{
		i = 0;
		while (data[counter][i])
		{
			put_square(data[counter][i], mlx, coords[0], coords[1]);
			i++;
			coords[0] += 31;
		}
		if (i == 0)
			break ;
		coords[1] += 31;
		coords[0] = 0;
	}
	//mlx->minimap.img = image_dup(mlx->mlx, mlx->img.img);
	draw_player(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img_ptr, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img_ptr);
}
