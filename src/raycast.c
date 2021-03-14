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

static float get_distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

static void calculate_ray_angle(t_rc_utils *rc_utils, float ray_angle)
{
	rc_utils->is_facing_down = ray_angle > 0 && ray_angle < PI;
	rc_utils->is_facing_up = !rc_utils->is_facing_down;
	rc_utils->is_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	rc_utils->is_facing_left = !rc_utils->is_facing_right;
}

static void init_rc_utils_horz(t_rc_utils *rc_utils, t_player *player, float ray_angle)
{
	rc_utils->found_horz_wall_hit = false;
	rc_utils->horz_wall_hit_x = 0;
	rc_utils->horz_wall_hit_y = 0;
	rc_utils->y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	rc_utils->y_intercept += rc_utils->is_facing_down ? TILE_SIZE : 0;
	rc_utils->x_intercept = player->x + (rc_utils->y_intercept - player->y) / tan(ray_angle);
	rc_utils->y_step = TILE_SIZE;
	rc_utils->y_step *= rc_utils->is_facing_up ? -1 : 1;
	rc_utils->x_step = TILE_SIZE / tan(ray_angle);
	rc_utils->x_step *= (rc_utils->is_facing_left && rc_utils->x_step > 0) ? -1 : 1;
	rc_utils->x_step *= (rc_utils->is_facing_right && rc_utils->x_step < 0) ? -1 : 1;
}

static void init_rc_utils_vert(t_rc_utils *rc_utils, t_player *player, float ray_angle)
{
	rc_utils->found_vert_wall_hit = false;
	rc_utils->vert_wall_hit_x = 0;
	rc_utils->vert_wall_hit_y = 0;
	rc_utils->x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
	rc_utils->x_intercept += rc_utils->is_facing_right ? TILE_SIZE : 0;
	rc_utils->y_intercept = player->y + (rc_utils->x_intercept - player->x) * tan(ray_angle);
	rc_utils->x_step = TILE_SIZE;
	rc_utils->x_step *= rc_utils->is_facing_left ? -1 : 1;
	rc_utils->y_step = TILE_SIZE * tan(ray_angle);
	rc_utils->y_step *= (rc_utils->is_facing_up && rc_utils->y_step > 0) ? -1 : 1;
	rc_utils->y_step *= (rc_utils->is_facing_down && rc_utils->y_step < 0) ? -1 : 1;
}

static bool is_around_window(t_rc_utils *rc_utils, t_map *map)
{
	if (rc_utils->horz_wall_hit_x < 0 && rc_utils->horz_wall_hit_x > map->window_width &&
		rc_utils->horz_wall_hit_y < 0 && rc_utils->horz_wall_hit_y > map->window_height)
		return (false);
	else
		return (true);
}

static void get_ray_distance_horz(t_rc_utils *rc_utils, t_player *player, t_map *map, float ray_angle)
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

#if DEBUG_ON
			printf("------\n");
			printf("x_to_check in horizonal check: %f\n", x_to_check);
			printf("y_to_check in horizonal check: %f\n", y_to_check);
#endif
			break;
		}
		else
		{
			next_horz_touch_x += rc_utils->x_step;
			next_horz_touch_y += rc_utils->y_step;
		}
	}
}

//--------------------
//|         |        |
//|   kabe  |        |
//----------.---------
//|         |        |
//|         |        |
//--------------------
//|         |        |
//|         |        |
//--------------------                a
//|         |        |
//|         |        |
//--------------------
//|         |        |
//|         |        |
//--------------------
//|         |        |
//|         |        |
//--------------------
//|         |        |
//|         |        |
//--------------------

static void get_ray_distance_vert(t_rc_utils *rc_utils, t_player *player, t_map *map, float ray_angle)
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

#if DEBUG_ON
			printf("------\n");
			printf("x_to_check in vertical check: %f\n", x_to_check);
			printf("y_to_check in vertical check: %f\n", y_to_check);
#endif

			break;
		}
		else
		{
			next_vert_touch_x += rc_utils->x_step;
			next_vert_touch_y += rc_utils->y_step;
		}
	}
}

static void calculate_horz_vert_distance(t_rc_utils *rc_utils, t_player *player)
{
	if (rc_utils->found_horz_wall_hit)
		rc_utils->horz_hit_distance = get_distance(player->x, player->y, rc_utils->horz_wall_hit_x, rc_utils->horz_wall_hit_y);
	else
		rc_utils->horz_hit_distance = FLT_MAX;
	if (rc_utils->found_vert_wall_hit)
		rc_utils->vert_hit_distance = get_distance(player->x, player->y, rc_utils->vert_wall_hit_x, rc_utils->vert_wall_hit_y);
	else
		rc_utils->horz_hit_distance = FLT_MAX;
}

static void fill_ray(t_rc_utils *rc_utils, t_ray *ray, float ray_angle)
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

t_ray cast_ray(t_params *params, t_player *player, float ray_angle)
{
	t_rc_utils rc_utils;
	t_ray ray;

	calculate_ray_angle(&rc_utils, ray_angle);
	init_rc_utils_horz(&rc_utils, player, ray_angle);
	get_ray_distance_horz(&rc_utils, player, &params->map, ray_angle);
	init_rc_utils_vert(&rc_utils, player, ray_angle);
	get_ray_distance_vert(&rc_utils, player, &params->map, ray_angle);
	calculate_horz_vert_distance(&rc_utils, player);
	fill_ray(&rc_utils, &ray, ray_angle);

	return (ray);
}
