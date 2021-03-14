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

static bool is_forbidden_char(char c)
{
	if (c >= '0' && c <= '2')
		return (false);
	else if (c == ' ')
		return (false);
	else
		return (true);
}



void	check_map_info(t_params *params)
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

void	check_map(t_params *params)
{
	check_map_info(params);
	//check_map_is_closed(&params->map);
}
