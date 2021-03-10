/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamaya <yhakamaya@student.42tokyo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:47:16 by yhakamaya         #+#    #+#             */
/*   Updated: 2021/02/22 16:10:29 by yhakamaya        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

int Map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void render_minimap(t_params *params)
{
	int i;
	int j;
	int x;
	int y;
	int tile_color;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			tile_color = Map[i][j] != 0 ? 111 : 0;

			render_rect(x, y, TILE_SIZE, TILE_SIZE, tile_color, &params->img);
			j++;
		}
		i++;
	}
}

bool is_inside_map(t_params *params, int x, int y)
{
	return (x >= 0 && x < MAP_NUM_COLS * TILE_SIZE && y >= 0 && y < MAP_NUM_ROWS * TILE_SIZE);
}

t_rays cast_ray(t_params *params, t_player *player, float ray_angle)
{
	ray_angle = normalize_angle(ray_angle);

	bool is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	bool is_ray_facing_up = !is_ray_facing_down;

	bool is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	bool is_ray_facing_left = ray_angle > 0 && ray_angle < PI;

	float x_intercept, y_intercept;
	float x_step, y_step;

	bool found_horz_wall_hit = false;
	float horz_wall_hit_x = 0;
	float horz_wall_hit_y = 0;
	int horz_wall_content = 0;

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

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= WINDOW_WIDTH && next_horz_touch_y <= WINDOW_HEIGHT)
	{
		float x_to_check = next_horz_touch_x;
		float y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 0);

		if (map_has_wall_at(x_to_check, x_to_check))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = Map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
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
	int vert_wall_content = 0;

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

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH && next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT)
	{
		float x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 0);
		float y_to_check = next_vert_touch_y;

		if (map_has_wall_at(x_to_check, y_to_check))
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

	t_rays ray;

	if (vert_hit_distance < horz_hit_distance)
	{
		ray.distance = vert_hit_distance;
		ray.wall_hit_x = vert_wall_hit_x;
		ray.wall_hit_y = vert_wall_hit_y;
		ray.wall_hit_content = vert_wall_content;
		ray.was_hit_vertical = true;
	}
	else
	{
		ray.distance = horz_hit_distance;
		ray.wall_hit_x = horz_wall_hit_x;
		ray.wall_hit_y = horz_wall_hit_y;
		ray.wall_hit_content = horz_wall_content;
		ray.was_hit_vertical = true;
	}
	ray.ray_angle = ray_angle;
	ray.is_ray_facing_down = is_ray_facing_down;
	ray.is_ray_facing_up = is_ray_facing_up;
	ray.is_ray_facing_left = is_ray_facing_left;
	ray.is_ray_facing_right = is_ray_facing_right;

	return ray;
}

void render_rays(t_params *params, t_player *player, t_img *img)
{
	int i;
	t_rays *rays;

	if (!(rays = malloc(sizeof(t_rays) * NUM_RAYS)))
		return;
	i = 0;
	while (i < NUM_RAYS)
	{
		rays[i] = cast_ray(params, player, player->rotation_angle - FOV_ANGLE * (0.5 - i / (float)WINDOW_WIDTH));
		render_line(img, player->x, player->y, rays[i].wall_hit_x, rays[i].wall_hit_y, PLAYER_COLOR);
		i++;
	}
	free(rays);
}

///////////////////////////////////////////
// serious error occurs in render_rays() //
///////////////////////////////////////////
void render_everything(t_params *params)
{
	refresh_img(&params->img);

	render_player(&params->player, &params->img);
	render_minimap(params);
	//render_rays(params, &params->player, &params->img);

	mlx_put_image_to_window(params->mlx.mlx_ptr, params->mlx.win_ptr, params->img.img, 0, 0);
}

void move_player(t_player *player, t_img *img)
{
	// printf("move_player() called\n");

	player->rotation_angle += player->turn_direction * player->turn_speed;

	player->rotation_angle = normalize_angle(player->rotation_angle);
	float move_step = player->walk_direction * player->walk_speed;
	float new_player_x = player->x + cos(player->rotation_angle) * move_step;
	float new_player_y = player->y + sin(player->rotation_angle) * move_step;

	if (has_wall_at(new_player_x, new_player_y))
		return;
	else
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}

void exit_game(t_mlx *mlx_ptr, t_mlx *win_ptr)
{
	mlx_destroy_window(mlx_ptr, win_ptr);
	exit(0);
}

int main(void)
{
	t_params params;

	// setvbuf below will be used when we debug using printf
	setvbuf(stdout, (char *)NULL, _IONBF, 0);

	// init some info
	params.mlx.mlx_ptr = mlx_init();
	params.mlx.win_ptr = mlx_new_window(params.mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	init_player(&params.player);

	// create a image on the window
	params.img.img = mlx_new_image(params.mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	params.img.addr = mlx_get_data_addr(params.img.img, &params.img.bits_per_pixel, &params.img.line_length, &params.img.endian);

	// render a player and push the image to the window
	render_player(&params.player, &params.img);
	render_minimap(&params);
	mlx_put_image_to_window(params.mlx.mlx_ptr, params.mlx.win_ptr, params.img.img, 0, 0);

	// accept key input and call some function via process_input()
	mlx_hook(params.mlx.win_ptr, X_EVENT_KEY_PRESSED, 1L << 0, key_pressed, &params);
	mlx_hook(params.mlx.win_ptr, X_EVENT_KEY_RELEASED, 1L << 0, key_released, &params);

	// make the game continuous
	mlx_loop(params.mlx.mlx_ptr);

	return (0);
}
