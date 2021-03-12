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

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void init_player(t_player *player, t_map *map)
{
	player->x = map->window_width / 2;
	player->y = map->window_height / 2;
	player->color = PLAYER_COLOR;
	player->width = PLAYER_DIAMETER;
	player->height = PLAYER_DIAMETER;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = 0;
	player->walk_speed = PLAYER_WALK_SPEED;
	player->turn_speed = PLAYER_TURN_SPEED;
}

// void init_map(t_map *map)
// {
// 	map->window_width = WINDOW_WIDTH;
// 	map->window_height = WINDOW_HEIGHT;
// 	// map->north_pass = ;
// 	// map->south_pass = ;
// 	// map->west_pass = ;
// 	// map->east_pass = ;
// 	// map->sprite_pass = ;
// 	// map->floor_rgb = ;
// 	// map->ceilling_rgb = ;
// 	// map->grid = ;
// }

float normalize_angle(float rotation_angle)
{
	rotation_angle = fmod(rotation_angle, 2 * PI);
	rotation_angle += rotation_angle < 0 ? 2 * PI : 0;

	return (rotation_angle);
}

bool has_wall_at(int x, int y, t_map *map)
{
	if (x < 0 || x > map->window_width || y < 0 || y > map->window_height)
		return true;
	return false;
}

bool map_has_wall_at(float x, float y, t_map *map)
{
	if (x < 0 || x > map->window_width || y < 0 || y > map->window_height)
		return true;
	int map_grid_index_x = floor(x / TILE_SIZE);
	int map_grid_index_y = floor(y / TILE_SIZE);

	return (map->grid[map_grid_index_y][map_grid_index_x] != 0);
	// return (Map[map_grid_index_y][map_grid_index_x] != 0);
}

float get_distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool is_inside_map(t_params *params, int x, int y)
{
	return (x >= 0 && x < MAP_NUM_COLS * TILE_SIZE && y >= 0 && y < MAP_NUM_ROWS * TILE_SIZE);
}

void refresh_img(t_img *img, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->window_width)
	{
		j = 0;
		while (j < map->window_height)
		{
			my_mlx_pixel_put(img, i, j, COLOR_BLACK);
			j++;
		}
		i++;
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

	/////////////////////////////////////////////////
	// serious error occurs in render_everything() //
	/////////////////////////////////////////////////
	render_everything(params);

	return (1);
}
