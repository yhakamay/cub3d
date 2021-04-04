/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:24:47 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/15 13:24:48 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

void	init_g_val(t_params *params)
{
	g_wall_strip_width = 1;
	g_num_rays = params->map.window_width / g_wall_strip_width;
	g_num_sprites = 0;
}

void	init_player(t_player *player)
{
	player->color = PLAYER_COLOR;
	player->width = PLAYER_DIAMETER;
	player->height = PLAYER_DIAMETER;
	player->turn_direction = 0;
	player->walk_direction_vert = 0;
	player->walk_direction_horz = 0;
	player->walk_speed = PLAYER_WALK_SPEED;
	player->turn_speed = PLAYER_TURN_SPEED;
}

void	init_rc_utils_horz(
			t_rc_utils *rc_u, t_player *p, float angle)
{
	rc_u->found_horz_wall_hit = false;
	rc_u->horz_wall_hit_x = 0;
	rc_u->horz_wall_hit_y = 0;
	rc_u->y_intercept = floor(p->y / TILE_SIZE) * TILE_SIZE;
	rc_u->y_intercept += rc_u->is_facing_down ? TILE_SIZE : 0;
	rc_u->x_intercept = p->x + (rc_u->y_intercept - p->y) / tan(angle);
	rc_u->y_step = TILE_SIZE;
	rc_u->y_step *= rc_u->is_facing_up ? -1 : 1;
	rc_u->x_step = TILE_SIZE / tan(angle);
	rc_u->x_step *= (rc_u->is_facing_left && rc_u->x_step > 0) ? -1 : 1;
	rc_u->x_step *= (rc_u->is_facing_right && rc_u->x_step < 0) ? -1 : 1;
}

void	init_rc_utils_vert(
			t_rc_utils *rc_u, t_player *p, float angle)
{
	rc_u->found_vert_wall_hit = false;
	rc_u->vert_wall_hit_x = 0;
	rc_u->vert_wall_hit_y = 0;
	rc_u->x_intercept = floor(p->x / TILE_SIZE) * TILE_SIZE;
	rc_u->x_intercept += rc_u->is_facing_right ? TILE_SIZE : 0;
	rc_u->y_intercept = p->y + (rc_u->x_intercept - p->x) * tan(angle);
	rc_u->x_step = TILE_SIZE;
	rc_u->x_step *= rc_u->is_facing_left ? -1 : 1;
	rc_u->y_step = TILE_SIZE * tan(angle);
	rc_u->y_step *= (rc_u->is_facing_up && rc_u->y_step > 0) ? -1 : 1;
	rc_u->y_step *= (rc_u->is_facing_down && rc_u->y_step < 0) ? -1 : 1;
}
