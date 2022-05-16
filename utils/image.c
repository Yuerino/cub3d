/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:09:03 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/11 18:51:39 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <mlx_int.h>
#include "libft.h"

/**
 * @brief Make a copy of a mlx image
 * @param img Image pointer of which you want to duplicate
 * @return void* New allocated image pointer duplicated from img
 */
void	*image_dup(void *mlx, void *img)
{
	void	*new_img;
	int		width;
	int		height;

	if (!mlx || !img)
		return ((void *)0);
	width = ((t_img *)img)->width;
	height = ((t_img *)img)->height;
	new_img = mlx_new_image(mlx, width, height);
	if (!new_img)
		return ((void *)0);
	ft_memmove(((t_img *)new_img)->data, ((t_img *)img)->data,
		(width + 32) * height * 4);
	return (new_img);
}

/**
 * @brief Clear data address of this image
 * @return void* Pointer of the same image
 */
void	*clear_image(void *img)
{
	int		width;
	int		height;

	width = ((t_img *)img)->width;
	height = ((t_img *)img)->height;
	ft_bzero(((t_img *)img)->data, (width + 32) * height * 4);
	return (img);
}

/**
 * @brief Put source image to destination image
 * @warning Use only if src size is less than dest size (and offset)
 * @param dest Pointer of destination image
 * @param src Pointer of source image
 * @param x_offset x start point of source on destination
 * @param y_offset y start point of source on destination
 */
void	put_image_to_image(void *dest, void *src, int x_offset, int y_offset)
{
	int		y;
	char	*dest_offset;
	char	*src_offset;

	y = y_offset;
	while (y <= ((t_img *)dest)->height)
	{
		dest_offset = ((t_img *)dest)->data + y * \
			((t_img *)dest)->size_line + x_offset * (((t_img *)dest)->bpp / 8);
		src_offset = ((t_img *)src)->data + \
			(y - y_offset) * ((t_img *)src)->size_line;
		ft_memmove(dest_offset, src_offset, (((t_img *)src)->width * 4));
		y++;
	}
}
