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

t_ray cast_ray(t_params *params, t_player *player, float ray_angle)
{
    ray_angle = normalize_angle(ray_angle);

    bool is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
    bool is_ray_facing_up = !is_ray_facing_down;

    bool is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    bool is_ray_facing_left = !is_ray_facing_right;

    float x_intercept, y_intercept;
    float x_step, y_step;

    bool found_horz_wall_hit = false;
    float horz_wall_hit_x = 0;
    float horz_wall_hit_y = 0;
    //int horz_wall_content = 0;

    y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    y_intercept += is_ray_facing_down ? TILE_SIZE : 0;

    x_intercept = player->x + (y_intercept - player->y) / tan(ray_angle);

    y_step = TILE_SIZE;
    y_step *= is_ray_facing_up ? -1 : 1;

    x_step = TILE_SIZE / tan(ray_angle);
    x_step = (is_ray_facing_left && x_step > 0) ? -1 : 1;
    x_step = (is_ray_facing_right && x_step < 0) ? -1 : 1;

    float next_horz_touch_x = x_intercept;
    float next_horz_touch_y = y_intercept;

    while (is_inside_map(params, next_horz_touch_x, next_horz_touch_y))
    {
        float x_to_check = next_horz_touch_x;
        float y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 0);

        if (map_has_wall_at(x_to_check, x_to_check, &params->map))
        {
            horz_wall_hit_x = next_horz_touch_x;
            horz_wall_hit_y = next_horz_touch_y;
            found_horz_wall_hit = true;
            break;
        }
        else
        {
            next_horz_touch_x += x_step;
            next_horz_touch_y += y_step;
        }
    }

    bool found_vert_wall_hit = false;
    float vert_wall_hit_x = 0;
    float vert_wall_hit_y = 0;

    x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    x_intercept += is_ray_facing_right ? TILE_SIZE : 0;

    y_intercept = player->y + (x_intercept - player->x) * tan(ray_angle);

    x_step = TILE_SIZE;
    x_step *= is_ray_facing_left ? -1 : 1;

    y_step = TILE_SIZE * tan(ray_angle);
    y_step *= (is_ray_facing_up && y_step > 0) ? -1 : 1;
    y_step *= (is_ray_facing_down && y_step < 0) ? -1 : 1;

    float next_vert_touch_x = x_intercept;
    float next_vert_touch_y = y_intercept;

    while (is_inside_map(params, next_vert_touch_x, next_vert_touch_y))
    {
        float x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 0);
        float y_to_check = next_vert_touch_y;

        if (map_has_wall_at(x_to_check, y_to_check, &params->map))
        {
            vert_wall_hit_x = next_vert_touch_x;
            vert_wall_hit_y = next_vert_touch_y;
            found_vert_wall_hit = true;
            break;
        }
        else
        {
            next_vert_touch_x = x_step;
            next_vert_touch_y = y_step;
        }
    }

    float horz_hit_distance = found_horz_wall_hit ? get_distance(player->x, player->y, horz_wall_hit_x, horz_wall_hit_y) : FLT_MAX;
    float vert_hit_distance = found_vert_wall_hit ? get_distance(player->x, player->y, vert_wall_hit_x, vert_wall_hit_y) : FLT_MAX;

    t_ray ray;

    if (vert_hit_distance < horz_hit_distance)
    {
        ray.distance = vert_hit_distance;
        ray.wall_hit_x = vert_wall_hit_x;
        ray.wall_hit_y = vert_wall_hit_y;
        ray.was_hit_vertical = true;
    }
    else
    {
        ray.distance = horz_hit_distance;
        ray.wall_hit_x = horz_wall_hit_x;
        ray.wall_hit_y = horz_wall_hit_y;
        ray.was_hit_vertical = false;
    }
    ray.ray_angle = ray_angle;
    return ray;
}
