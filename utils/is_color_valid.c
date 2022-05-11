/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_color_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:48:56 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 23:03:03 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Check if RGB color is valid
 * @param color Integer array size of 3 that holds R, G, B value
 * @return 1 if valid otherwise 0
 */
int	is_color_valid(int *color)
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
