/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:28:47 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/10 17:28:49 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

int g_num_rays;
int g_wall_strip_width;

int			exit_game(void)
{
	exit(0);
}

float		normalize_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	angle += angle < 0 ? TWO_PI : 0;
	return (angle);
}

bool		has_wall_at(float x, float y, t_map *map)
{
	int tile_index_x;
	int tile_index_y;

	if (x < 0 || x > map->window_width || y < 0 || y > map->window_height)
		return (true);
	tile_index_x = x / TILE_SIZE;
	tile_index_y = y / TILE_SIZE;
	return (map->grid[tile_index_y][tile_index_x] == '1');
}
