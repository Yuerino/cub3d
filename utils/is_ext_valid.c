/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ext_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:50:15 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 22:23:55 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Check if the map file has correct extension
 * @param filename Path to the file
 * @param ext The extension to compare to
 * @return 1 if yes otherwise 0
 */
int	is_ext_valid(char *filename, char *ext)
{
	char	*file_ext;

	file_ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(file_ext, ext, 5))
		return (0);
	return (1);
}
