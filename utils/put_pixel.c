/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:09:26 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/11 19:14:11 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

/**
 * @brief Put pixel color to the image
 */
void	ft_mlx_pixel_put(void *img_ptr, int x, int y, int color)
{
	char	*dst;
	char	*adr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	adr = mlx_get_data_addr(img_ptr, &bits_per_pixel, \
		&line_length, &endian);
	dst = adr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * @note this doesn't support tranparency
 * @brief Put pixel RGB color to the image
 * @param color Integer array size of 3 that has R, G, B value
 */
void	ft_mlx_pixel_put_rgb(void *img_ptr, int x, int y, int rgb[3])
{
	char	*dst;
	char	*adr;
	int		bits_per_pixel;
	int		line_length;
	int		temp;

	adr = mlx_get_data_addr(img_ptr, &bits_per_pixel, \
		&line_length, &temp);
	temp = (0xFF << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	dst = adr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = temp;
}
