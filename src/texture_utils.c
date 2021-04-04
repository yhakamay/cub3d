/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 23:55:38 by yhakamay          #+#    #+#             */
/*   Updated: 2021/04/04 23:55:40 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

char	*get_color_addr(t_img *img, int row, int col, int height)
{
	char	*color_addr;

	color_addr = img->addr + (int)roundf(row * img->height / height) *
		img->line_length + (int)roundf(col * img->width / height) *
		(img->bits_per_pixel / 8);
	return (color_addr);
}

char	*get_color_addr_reverse(t_img *img, int row, int col, int height)
{
	char	*color_addr;

	color_addr = img->addr + ((int)roundf(row * img->height / height) + 1) *
		img->line_length - (int)roundf(col * img->width / height + 1) *
		(img->bits_per_pixel / 8);
	return (color_addr);
}

bool	is_inside_window(int height, int window_height, int i)
{
	return (window_height / 2 - height / 2 + i >= 0 &&
				window_height / 2 - height / 2 + i < window_height);
}
