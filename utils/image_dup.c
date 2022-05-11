/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:09:03 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 23:42:48 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <mlx_int.h>
#include "libft.h"

/**
 * @todo: haven't tested this
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
