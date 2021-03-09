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

void render_player(t_player *player, t_img *img)
{
	render_rect(player->x,
				player->y,
				player->width,
				player->height,
				player->color,
				img);
	render_line(player->x,
				player->y,
				player->rotation_angle,
				PLAYER_RAY_LENGTH,
				player->color,
				img);
}

void render_everything(t_params *params)
{
	render_player(&params->player, &params->img);
	render_minimap(params);

	mlx_put_image_to_window(params->mlx.mlx_ptr, params->mlx.win_ptr, params->img.img, 0, 0);
}

void move_player(t_player *player, t_img *img)
{
	player->rotation_angle += player->turn_direction * player->turn_speed;

	if (player->rotation_angle > 2 * PI)
		player->rotation_angle = 0;
	if (player->rotation_angle < 0)
		player->rotation_angle = 2 * PI;
	float move_step = player->walk_direction * player->walk_speed;
	float new_player_x = player->x + cos(player->rotation_angle) * move_step;
	float new_player_y = player->y + sin(player->rotation_angle) * move_step;

	player->x = new_player_x;
	player->y = new_player_y;

	//printf("player.rotation_angle: %f\n", player->rotation_angle);
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

	// render a player and push the image to window
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
