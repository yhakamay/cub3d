/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:04:49 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/12 17:04:50 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

static void		get_ray_distance_horz(
					t_rc_utils *rc_utils, t_player *player,
					t_map *map, float ray_angle)
{
	float next_horz_touch_x;
	float next_horz_touch_y;
	float x_to_check;
	float y_to_check;

	next_horz_touch_x = rc_utils->x_intercept;
	next_horz_touch_y = rc_utils->y_intercept;
	while (is_around_window(rc_utils, map))
	{
		x_to_check = next_horz_touch_x;
		y_to_check = next_horz_touch_y + (rc_utils->is_facing_up ? -1 : 0);
		if (has_wall_at(x_to_check, y_to_check, map))
		{
			rc_utils->horz_wall_hit_x = next_horz_touch_x;
			rc_utils->horz_wall_hit_y = next_horz_touch_y;
			rc_utils->found_horz_wall_hit = true;
			break ;
		}
		else
		{
			next_horz_touch_x += rc_utils->x_step;
			next_horz_touch_y += rc_utils->y_step;
		}
	}
}

static void		get_ray_distance_vert(
					t_rc_utils *rc_utils, t_player *player,
					t_map *map, float ray_angle)
{
	float next_vert_touch_x;
	float next_vert_touch_y;
	float x_to_check;
	float y_to_check;

	next_vert_touch_x = rc_utils->x_intercept;
	next_vert_touch_y = rc_utils->y_intercept;
	while (is_around_window(rc_utils, map))
	{
		x_to_check = next_vert_touch_x + (rc_utils->is_facing_left ? -1 : 0);
		y_to_check = next_vert_touch_y;
		if (has_wall_at(x_to_check, y_to_check, map))
		{
			rc_utils->vert_wall_hit_x = next_vert_touch_x;
			rc_utils->vert_wall_hit_y = next_vert_touch_y;
			rc_utils->found_vert_wall_hit = true;
			break ;
		}
		else
		{
			next_vert_touch_x += rc_utils->x_step;
			next_vert_touch_y += rc_utils->y_step;
		}
	}
}

static void		calc_horz_vert_distance(t_rc_utils *rc_utils, t_player *player)
{
	if (rc_utils->found_horz_wall_hit)
		rc_utils->horz_hit_distance = get_distance(
			player->x,
			player->y,
			rc_utils->horz_wall_hit_x,
			rc_utils->horz_wall_hit_y);
	else
		rc_utils->horz_hit_distance = FLT_MAX;
	if (rc_utils->found_vert_wall_hit)
		rc_utils->vert_hit_distance = get_distance(
			player->x,
			player->y,
			rc_utils->vert_wall_hit_x,
			rc_utils->vert_wall_hit_y);
	else
		rc_utils->horz_hit_distance = FLT_MAX;
}

static void		fill_ray(t_rc_utils *rc_utils, t_ray *ray, float ray_angle)
{
	if (rc_utils->vert_hit_distance < rc_utils->horz_hit_distance)
	{
		ray->distance = rc_utils->vert_hit_distance;
		ray->wall_hit_x = rc_utils->vert_wall_hit_x;
		ray->wall_hit_y = rc_utils->vert_wall_hit_y;
		ray->was_hit_vertical = true;
	}
	else
	{
		ray->distance = rc_utils->horz_hit_distance;
		ray->wall_hit_x = rc_utils->horz_wall_hit_x;
		ray->wall_hit_y = rc_utils->horz_wall_hit_y;
		ray->was_hit_vertical = false;
	}
	ray->ray_angle = ray_angle;
}

t_ray			cast_ray(t_params *params, t_player *player, float ray_angle)
{
	t_rc_utils	rc_utils;
	t_ray		ray;

	calculate_ray_angle(&rc_utils, ray_angle);
	init_rc_utils_horz(&rc_utils, player, ray_angle);
	get_ray_distance_horz(&rc_utils, player, &params->map, ray_angle);
	init_rc_utils_vert(&rc_utils, player, ray_angle);
	get_ray_distance_vert(&rc_utils, player, &params->map, ray_angle);
	calc_horz_vert_distance(&rc_utils, player);
	fill_ray(&rc_utils, &ray, ray_angle);
	return (ray);
}
