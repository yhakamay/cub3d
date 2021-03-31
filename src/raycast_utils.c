/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:31:17 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/15 13:31:18 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

float	get_distance(float x1, float y1, float x2, float y2)
{
	//printf("get_distance\n");
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	calculate_ray_angle(t_rc_utils *rc_utils, float ray_angle)
{
	rc_utils->is_facing_down = ray_angle > 0 && ray_angle < PI;
	rc_utils->is_facing_up = !rc_utils->is_facing_down;
	rc_utils->is_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	rc_utils->is_facing_left = !rc_utils->is_facing_right;
}

bool	is_around_window(t_rc_utils *rc_utils, t_map *map)
{
	if (rc_utils->horz_wall_hit_x < 0 &&
		rc_utils->horz_wall_hit_x > map->window_width &&
		rc_utils->horz_wall_hit_y < 0
		&& rc_utils->horz_wall_hit_y > map->window_height)
		return (false);
	else
		return (true);
}
