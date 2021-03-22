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

static void	write_bmp_header(t_params *params, int fd)
{
	unsigned int size;
	unsigned int offset;

	offset = FILE_H_SIZE + INFO_H_SIZE;
	size = offset + (
		params->map.window_height *
		params->map.window_width * 4);
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0", 2);
	write(fd, "\0\0", 2);
	write(fd, &offset, 4);
}

static void	write_bmp_info(t_params *params, int fd)
{
	unsigned int	info_size;
	unsigned int	plane;
	unsigned int	bpp;
	int				i;

	i = 0;
	info_size = INFO_H_SIZE;
	plane = 1;
	bpp = 32;
	write(fd, &info_size, 4);
	write(fd, &(params->map.window_width), 4);
	write(fd, &(params->map.window_height), 4);
	write(fd, &plane, 2);
	write(fd, &bpp, 2);
	while (i++ < 24)
		write(fd, "\0", 1);
}

static void	write_bmp_img(t_params *params, int fd)
{
	int index_x;
	int index_y;
	int *color_p;
	int color;

	index_y = 0;
	while (index_y < params->map.window_height)
	{
		index_x = 0;
		while (index_x < params->map.window_width)
		{
			color_p = (int *)(
				params->img.addr +
				((params->map.window_height - index_y - 1) *
				(params->img.line_length)) +
				index_x * (params->img.bits_per_pixel / 8));
			color = *color_p;
			write(fd, &color, 4);
			index_x++;
		}
		index_y++;
	}
}

void		save_screenshot(t_params *params)
{
	int	fd;

	render_everything(params);
	fd = open("./screenshot.bmp",
	O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
	{
		screenshot_err();
		exit_game();
	}
	write_bmp_header(params, fd);
	write_bmp_info(params, fd);
	write_bmp_img(params, fd);
	close(fd);
	exit_game();
}
