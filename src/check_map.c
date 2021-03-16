/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuki <matsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:05:20 by matsuki           #+#    #+#             */
/*   Updated: 2021/03/14 14:02:02 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

static bool	is_player(t_params *params, char c)
{
	if (c == 'N')
		params->player.rotation_angle = 1.5 * PI;
	else if (c == 'S')
		params->player.rotation_angle = 0.5 * PI;
	else if (c == 'E')
		params->player.rotation_angle = 0;
	else if (c == 'W')
		params->player.rotation_angle = PI;
	else
		return (false);
	return (true);
}

static bool	is_forbidden_char(char c)
{
	if (c >= '0' && c <= '2')
		return (false);
	else if (c == ' ')
		return (false);
	else
		return (true);
}

int		check_map_is_closed(t_map *map, int x, int y)
{
	int	ret;

	if (x < 0 || x > 200 || y < 0 || y > 200)
		return (1);
	else if (map->reached[y][x] == true)
		return (0);
	map->reached[y][x] = true;
	if (map->grid[y][x] == '1')
		return (0);
	else if (map->grid[y][x] == '\0')
		return (1);
	ret = 0;
	ret += check_map_is_closed(map, x + 1, y);
	ret += check_map_is_closed(map, x - 1, y);
	ret += check_map_is_closed(map, x, y + 1);
	ret += check_map_is_closed(map, x, y - 1);
	return (ret);
}

void		check_map_info(t_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (params->map.grid[i][0] != '\0')
	{
		j = 0;
		while (params->map.grid[i][j] != '\0')
		{
			if (is_player(params, params->map.grid[i][j]))
			{
				params->player.x = (j + 0.5) * TILE_SIZE;
				params->player.y = (i + 0.5) * TILE_SIZE;
				params->map.grid[i][j] = '0';
			}
			else if (is_forbidden_char(params->map.grid[i][j]))
			{
				use_forbidden_char_err();
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void		check_map(t_params *params)
{
	int tile_index_x;
	int tile_index_y;

	check_map_info(params);
	tile_index_x = floor(params->player.x / TILE_SIZE);
	tile_index_y = floor(params->player.y / TILE_SIZE);
	if (check_map_is_closed(&params->map, tile_index_x, tile_index_y))
	{
		map_is_not_closed_err();
		exit(0);
	}
}