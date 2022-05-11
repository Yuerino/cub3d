/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 00:59:20 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 20:16:16 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

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

/**
 * @brief Find length of double char pointer array
 * @return int Length of the array
 */
int	carray_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/**
 * @brief Expand the double char pointer to current size + 1
 * and free current one
 * @param array The double char pointer to expand, if empty, return
 * a new double char array size of 2
 * @return char** The new size-increased double char pointer
 */
char	**carray_expand(char **array)
{
	char	**new_arr;

	if (!array)
		return (ft_calloc(2, sizeof(char *)));
	new_arr = ft_calloc(carray_len(array) + 2, sizeof(char *));
	if (!new_arr)
		return (NULL);
	ft_memmove(new_arr, array, carray_len(array) * sizeof(char *));
	free(array);
	return (new_arr);
}
