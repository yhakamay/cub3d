/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:58:34 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/31 15:58:35 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

bool	is_player(t_params *params, char c)
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

bool	is_sprite(char c)
{
	return (c == '2');
}

bool	is_forbidden_char(char c)
{
	if (c >= '0' && c <= '2')
		return (false);
	else if (c == ' ')
		return (false);
	else
		return (true);
}

int		is_map_closed(t_map *map, int x, int y)
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
	ret += is_map_closed(map, x + 1, y);
	ret += is_map_closed(map, x - 1, y);
	ret += is_map_closed(map, x, y + 1);
	ret += is_map_closed(map, x, y - 1);
	return (ret);
}
