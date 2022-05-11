/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:55:02 by cthien-h          #+#    #+#             */
/*   Updated: 2022/05/10 21:14:37 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Print the error message to standard error
 * and (optional) free cub3d data
 * @param err Error message
 * @param data (Optional) Cub3d's data to be freed
 * @return 0 for error
 */
int	print_error(char *err, t_cub3d *data)
{
	ft_putendl_fd(err, STDERR_FILENO);
	if (data)
		free_data(data);
	return (0);
}

/**
 * @brief Print the errno message with (optional) error message
 * and (optional) free cub3d data
 * @param err (Optional) Error message
 * @param data (Optional) Cub3d's data to be freed
 * @return 0 for error
 */
int	print_perror(char *err, t_cub3d *data)
{
	perror(err);
	if (data)
		free_data(data);
	return (0);
}

/**
 * @brief Print the error message and (optional)
 * free cub3d data then exit error
 * @param err Error message
 * @param data (Optional) Cub3d's data to be freed
 */
void	exit_error(char *err, t_cub3d *data)
{
	ft_putendl_fd(err, STDERR_FILENO);
	if (data)
		free_data(data);
	exit(EXIT_FAILURE);
}

/**
 * @brief Print errno message with (optional) error message and (optional)
 * free cub3d data then exit error
 * @param err (Optional) Error message
 * @param data (Optional) Cub3d's data to be freed
 */
void	exit_perror(char *err, t_cub3d *data)
{
	perror(err);
	if (data)
		free_data(data);
	exit(EXIT_FAILURE);
}
