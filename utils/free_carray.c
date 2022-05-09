/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_carray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 00:59:20 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 01:53:43 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief Free all content inside double char pointer and itself
 */
void	free_carray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
