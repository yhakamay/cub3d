/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 23:42:35 by yhakamay          #+#    #+#             */
/*   Updated: 2021/04/04 23:42:35 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

void	render_east_texture(t_params *params, t_ray *ray, int x, int height)
{
	char	*color_addr;
	float	col;
	int		i;
	int		j;

	col = ray->length_from_leftside * height / TILE_SIZE;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < g_wall_strip_width)
		{
			color_addr = get_color_addr(&params->texture.east, i,
							col + j, height);
			if (is_inside_window(height, params->map.window_height, i))
			{
				draw_pixel(&params->img, x,
					params->map.window_height / 2 - height / 2 + i,
					*(int *)(color_addr));
			}
			j++;
		}
		i++;
	}
}

void	render_north_texture(t_params *params, t_ray *ray, int x, int height)
{
	char	*color_addr;
	float	col;
	int		i;
	int		j;

	col = ray->length_from_leftside * height / TILE_SIZE;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < g_wall_strip_width)
		{
			color_addr = get_color_addr(&params->texture.north, i,
							col + j, height);
			if (is_inside_window(height, params->map.window_height, i))
			{
				draw_pixel(&params->img, x,
					params->map.window_height / 2 - height / 2 + i,
					*(int *)(color_addr));
			}
			j++;
		}
		i++;
	}
}

void	render_west_texture(t_params *params, t_ray *ray, int x, int height)
{
	char	*color_addr;
	float	col;
	int		i;
	int		j;

	col = ray->length_from_leftside * height / TILE_SIZE;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < g_wall_strip_width)
		{
			color_addr = get_color_addr_reverse(&params->texture.west,
							i, col + j, height);
			if (is_inside_window(height, params->map.window_height, i))
			{
				draw_pixel(&params->img, x,
					params->map.window_height / 2 - height / 2 + i,
					*(unsigned int *)(color_addr));
			}
		}
	}
}

void	render_south_texture(t_params *params, t_ray *ray, int x, int height)
{
	char	*color_addr;
	float	col;
	int		i;
	int		j;

	col = ray->length_from_leftside * height / TILE_SIZE;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < g_wall_strip_width)
		{
			color_addr = get_color_addr_reverse(&params->texture.south,
							i, col + j, height);
			if (is_inside_window(height, params->map.window_height, i))
			{
				draw_pixel(&params->img, x,
					params->map.window_height / 2 - height / 2 + i,
					*(unsigned int *)(color_addr));
			}
		}
	}
}
