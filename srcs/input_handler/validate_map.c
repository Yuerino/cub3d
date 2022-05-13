/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 03:43:11 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/13 07:40:29 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the empty area at (x|y) is valid
 * and not opened to non-playable are
 * @param x x-coordination of the empty area
 * @param y y-coordination of the empty area
 * @return 1 if valid otherwise 0
 */
static int	is_valid_empty(char **map_data, int x, int y)
{
	if (map_data[y - 1][x] == ' ' || map_data[y + 1][x] == ' '
		|| map_data[y][x - 1] == ' ' || map_data[y][x + 1] == ' '
		|| map_data[y - 1][x - 1] == ' ' || map_data[y + 1][x + 1] == ' '
		|| map_data[y + 1][x - 1] == ' ' || map_data[y - 1][x + 1] == ' ')
		return (0);
	return (1);
}

/**
 * @brief Validate map, make sure map is surrounded by wall
 * @return 1 if valid otherwise 0
 */
int	validate_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->data[y])
	{
		x = 0;
		while (map->data[y][x])
		{
			if (map->data[y][x] == '0')
			{
				if (y == 0 || y == map->height - 1
					|| x == 0 || x == (int)ft_strlen(map->data[y]) - 1
					|| !is_valid_empty(map->data, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
