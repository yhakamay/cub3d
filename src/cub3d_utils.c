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
	float move_step_vert = player->walk_direction_vert * player->walk_speed;
	float move_step_horz = player->walk_direction_horz * player->walk_speed;
	float new_player_x = player->x + cos(player->rotation_angle) * move_step_vert - sin(player->rotation_angle) * move_step_horz;
	float new_player_y = player->y + sin(player->rotation_angle) * move_step_vert + cos(player->rotation_angle) * move_step_horz;

	if (has_wall_at(new_player_x, new_player_y, map))
		return;
	else
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}

#if DEBUG_ON
	printf("-----\n");
	printf("player.x:\t%d\nplayer.y:\t%d\n\n", player->x, player->y);
	printf("player.rotation_angle:\t%f\n\n\n", player->rotation_angle * 180 / PI);
#endif
}

int key_pressed(int keycode, t_params *params)
{
	if (keycode == KEY_ESC)
		exit_game(params->mlx.mlx_ptr, params->mlx.win_ptr);

	if (keycode == KEY_W)
		params->player.walk_direction_vert = 1; // move forward
	else if (keycode == KEY_S)
		params->player.walk_direction_vert = -1; // move backward
	else if (keycode == KEY_D)
		params->player.walk_direction_horz = 1; // move right
	else if (keycode == KEY_A)
		params->player.walk_direction_horz = -1; // move left
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
		params->player.walk_direction_vert = 0;
	else if (keycode == KEY_S)
		params->player.walk_direction_vert = 0;
	else if (keycode == KEY_D)
		params->player.walk_direction_horz = 0;
	else if (keycode == KEY_A)
		params->player.walk_direction_horz = 0;
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
