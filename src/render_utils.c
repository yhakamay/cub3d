/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 22:49:01 by yhakamay          #+#    #+#             */
/*   Updated: 2021/04/04 22:49:02 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

void		draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void		render_ceiling(t_img *img, t_map *map)
{
	int x_i;
	int y_i;

	x_i = -1;
	while (++x_i < map->window_width)
	{
		y_i = -1;
		while (++y_i < map->window_height / 2)
		{
			draw_pixel(img, x_i, y_i, COLOR_CYAN);
		}
	}
}

void		render_floor(t_img *img, t_map *map)
{
	int x_i;
	int y_i;

	x_i = -1;
	while (++x_i < map->window_width)
	{
		y_i = map->window_height / 2 - 1;
		while (++y_i < map->window_height)
		{
			draw_pixel(img, x_i, y_i, COLOR_GRAY);
		}
	}
}

void		render_walls(t_params *params, int i, int height, float ray_angle)
{
	if (params->rays[i].was_hit_vertical == true &&
		(ray_angle < 0.5 * PI || ray_angle > 1.5 * PI))
		render_west_texture(params, &params->rays[i],
			i * g_wall_strip_width, height);
	else if (params->rays[i].was_hit_vertical == true &&
		(ray_angle >= 0.5 * PI && ray_angle <= 1.5 * PI))
		render_east_texture(params, &params->rays[i],
			i * g_wall_strip_width, height);
	else if (params->rays[i].was_hit_vertical == false &&
		(ray_angle >= 0 && ray_angle < PI))
		render_north_texture(params, &params->rays[i],
			i * g_wall_strip_width, height);
	else if (params->rays[i].was_hit_vertical == false &&
		(ray_angle >= PI && ray_angle < 2 * PI))
		render_south_texture(params, &params->rays[i],
			i * g_wall_strip_width, height);
}
