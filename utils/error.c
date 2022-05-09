/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:55:02 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/09 18:55:28 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *err)
{
	ft_putendl_fd(err, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
