/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 21:09:42 by cthien-h          #+#    #+#             */
/*   Updated: 2021/05/14 19:33:41 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(int n)
{
	size_t			length;
	unsigned int	un;

	length = 1;
	un = n;
	if (n < 0)
	{
		length = 2;
		un = -n;
	}
	while (un > 9)
	{
		un /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	size_t			n_len;
	char			*str;
	unsigned int	un;

	n_len = num_len(n);
	str = (char *)ft_calloc(n_len + 1, sizeof(char));
	if (str)
	{
		un = n;
		if (n < 0)
		{
			un = -n;
			str[0] = '-';
		}
		str[n_len - 1] = '0';
		while (un > 0)
		{
			str[n_len - 1] = (un % 10) + 48;
			un /= 10;
			n_len--;
		}
	}
	return (str);
}
