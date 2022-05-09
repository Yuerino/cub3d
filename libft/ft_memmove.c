/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:00:35 by cthien-h          #+#    #+#             */
/*   Updated: 2021/05/13 14:19:19 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	index;

	i = 0;
	while (i < n)
	{
		if (dest > src)
			index = n - i - 1;
		else
			index = i;
		((char *)dest)[index] = ((char *)src)[index];
		i++;
	}
	return (dest);
}
