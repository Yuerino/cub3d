/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:20:27 by cthien-h          #+#    #+#             */
/*   Updated: 2021/05/16 17:01:54 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	const char	*little_begin;

	little_begin = little;
	i = 0;
	while (42)
	{
		if (!*little)
			return ((char *)(big + i - ft_strlen(little_begin)));
		if (big[i] == *little)
			little++;
		else
			little = little_begin;
		if (!big[i] || i >= len)
			break ;
		i++;
	}
	return (NULL);
}
