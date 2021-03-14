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

static void init_player(t_player *player, t_map *map)
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

int main(int argc, char **argv)
{
	t_params params;

#if DEBUG_ON
	setvbuf(stdout, (char *)NULL, _IONBF, 0);
#endif

	if (argc != 2)
		return (no_args_err());
	read_map(argv[1], &params.map);
	check_map(&params);
	params.mlx.mlx_ptr = mlx_init();
	params.mlx.win_ptr = mlx_new_window(params.mlx.mlx_ptr, params.map.window_width, params.map.window_height, WINDOW_TITLE);
	init_player(&params.player, &params.map);
	params.img.img = mlx_new_image(params.mlx.mlx_ptr, params.map.window_width, params.map.window_height);
	params.img.addr = mlx_get_data_addr(params.img.img, &params.img.bits_per_pixel, &params.img.line_length, &params.img.endian);
	render_everything(&params);
	mlx_hook(params.mlx.win_ptr, X_EVENT_KEY_PRESSED, 1L << 0, key_pressed, &params);
	mlx_hook(params.mlx.win_ptr, X_EVENT_KEY_RELEASED, 1L << 0, key_released, &params);
	mlx_loop(params.mlx.mlx_ptr);

	return (0);
}
