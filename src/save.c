/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 01:10:29 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/22 01:10:30 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

static void	write_bmp_file(t_params *params, int fd)
{
	int	x_i;
	int	y_i;
	int	*color_p;
	int	color;

	y_i = 0;
	while (y_i < params->map.window_height)
	{
		x_i = 0;
		while (x_i < params->map.window_width)
		{
			color_p = (int *)(params->)
		}
	}
}

static void	write_bmp_info(t_params *params, int fd)
{

}

static void	write_bmp_pixel(t_params *params, int fd)
{

}

void		save_screenshot(t_params *params)
{
	int	fd;

	fd = open("./screenshot.bmp", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
	{
		exit_game();
	}
	write_bmp_file(params, fd);
	write_bmp_info(params, fd);
	write_bmp_pixel(params, fd);
	close(fd);
	exit_game();
}
