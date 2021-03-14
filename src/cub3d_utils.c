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

void init_g_val(t_params *params)
{
	g_wall_strip_width = 2;
	g_num_rays = params->map.window_width / g_wall_strip_width;
}

float normalize_angle(float rotation_angle)
{
	rotation_angle = fmod(rotation_angle, TWO_PI);
	rotation_angle += rotation_angle < 0 ? TWO_PI : 0;

	return (rotation_angle);
}

void freeeee(void *malloced_var)
{
	free(malloced_var);
	malloced_var = NULL;
}

bool has_wall_at(float x, float y, t_map *map)
{
	int tile_index_x;
	int tile_index_y;

	if (x < 0 || x > map->window_width || y < 0 || y > map->window_height)
		return true;
	tile_index_x = floor(x / TILE_SIZE);
	tile_index_y = floor(y / TILE_SIZE);
	return (map->grid[tile_index_y][tile_index_x] != '0');
}

static void exit_game(t_mlx *mlx_ptr, t_mlx *win_ptr)
{
	mlx_destroy_window(mlx_ptr, win_ptr);
	exit(0);
}

static void move_player(t_player *player, t_img *img, t_map *map)
{
	player->rotation_angle += player->turn_direction * player->turn_speed;
	player->rotation_angle = normalize_angle(player->rotation_angle);
	float move_step = player->walk_direction * player->walk_speed;
	float new_player_x = player->x + cos(player->rotation_angle) * move_step;
	float new_player_y = player->y + sin(player->rotation_angle) * move_step;

	if (has_wall_at(new_player_x, new_player_y, map))
		return;
	else
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}

int key_pressed(int keycode, t_params *params)
{
	if (keycode == KEY_ESC)
		exit_game(params->mlx.mlx_ptr, params->mlx.win_ptr);

	if (keycode == KEY_W)
		params->player.walk_direction = 1; // move forward
	else if (keycode == KEY_S)
		params->player.walk_direction = -1; // move backward
	// if (keycode == KEY_D)
	// if (keycode == KEY_A)
	else if (keycode == KEY_ARROW_LEFT)
		params->player.turn_direction = 1;
	else if (keycode == KEY_ARROW_RIGHT)
		params->player.turn_direction = -1;
	else
		return (1);

	move_player(&params->player, &params->img, &params->map);
	render_everything(params);

	return (1);
}

int key_released(int keycode, t_params *params)
{
	if (keycode == KEY_W)
		params->player.walk_direction = 0;
	else if (keycode == KEY_S)
		params->player.walk_direction = 0;
	// if (keycode == KEY_D)
	// if (keycode == KEY_A)
	else if (keycode == KEY_ARROW_LEFT)
		params->player.turn_direction = 0;
	else if (keycode == KEY_ARROW_RIGHT)
		params->player.turn_direction = 0;
	else
		return (1);

	move_player(&params->player, &params->img, &params->map);
	render_everything(params);

	return (1);
}
