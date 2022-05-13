/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:48:56 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 07:41:07 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

/**
 * @brief Check if RGB color is valid
 * @param color Integer array size of 3 that holds R, G, B value
 * @return 1 if valid otherwise 0
 */
int	is_color_valid(int color[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Get hexa color from string r, g, b respectively
 * @param color Pointer of the integer you want to set hexa color to
 * @return 1 if success otherwise 0
 */
int	str_rgb_to_color(char *r, char *g, char *b, long long *color)
{
	int	rgb[3];

	rgb[0] = ft_atoi(r);
	rgb[1] = ft_atoi(g);
	rgb[2] = ft_atoi(b);
	if (!is_nbr(r) || !is_nbr(g) || !is_nbr(b)
		|| !is_color_valid(rgb))
		return (0);
	*color = (0xFF << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	return (1);
}
