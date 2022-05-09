/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 19:32:40 by cthien-h          #+#    #+#             */
/*   Updated: 2021/05/16 16:22:41 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	start_len;

	start_len = ft_strlen(s + start);
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > start_len)
		len = start_len;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str)
		ft_strlcpy(str, s + start, len + 1);
	return (str);
}
