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

void move_player(t_player *player, t_img *img, t_map *map)
{
	// printf("move_player() called\n");

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

int main(int argc, char **argv)
{
	t_params params;

	// setvbuf below will be used when we debug using printf
	setvbuf(stdout, (char *)NULL, _IONBF, 0);

	// init some info
	params.mlx.mlx_ptr = mlx_init();
	params.mlx.win_ptr = mlx_new_window(params.mlx.mlx_ptr, params.map.window_width, params.map.window_height, WINDOW_TITLE);
	init_player(&params.player, &params.map);
	// init_map(&params.map);

	// create a image on the window
	params.img.img = mlx_new_image(params.mlx.mlx_ptr, params.map.window_width, params.map.window_height);
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
