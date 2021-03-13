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

int main(int argc, char **argv)
{
	t_params params;

#if DEBUG_ON
	setvbuf(stdout, (char *)NULL, _IONBF, 0);
#endif

	if (argc != 2)
		return (no_args_err());

	// read .cub file
	read_map(argv[1], &params.map);

	////////////////////////// DEBUG //////////////////////////
	int i = 0;
	while (params.map.grid[i][0] != '\0')
	{
		printf("%s\n", params.map.grid[i]);
		i++;
	}
	////////////////////////// DEBUG //////////////////////////

	// init some info
	params.mlx.mlx_ptr = mlx_init();
	params.mlx.win_ptr = mlx_new_window(params.mlx.mlx_ptr, params.map.window_width, params.map.window_height, WINDOW_TITLE);
	init_player(&params.player, &params.map);

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
