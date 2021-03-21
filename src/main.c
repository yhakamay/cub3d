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

static void	setup(char *file_path, t_params *params)
{
	params->mlx.mlx_ptr = mlx_init();
	read_map(file_path, &params->map);
	check_map(params);
	init_g_val(params);
	params->mlx.win_ptr = mlx_new_window(
		params->mlx.mlx_ptr,
		params->map.window_width,
		params->map.window_height,
		WINDOW_TITLE);
	init_player(&params->player, &params->map);
	//params->img.img = mlx_xpm_file_to_image(
	//	params->mlx.mlx_ptr,
	//	"../textures/wall_n.xpm",
	//	&params->img.width,
	//	&params->img.height);
	params->img.img = mlx_new_image(
		params->mlx.mlx_ptr,
		params->map.window_width,
		params->map.window_height);
	params->img.addr = mlx_get_data_addr(
		params->img.img,
		&params->img.bits_per_pixel,
		&params->img.line_length,
		&params->img.endian);
}

int			main(int argc, char **argv)
{
	t_params	params;

	if (argc != 2)
		return (no_args_err());
	setup(argv[1], &params);
	render_everything(&params);
	mlx_hook(params.mlx.win_ptr, KEY_PRESSED, 1L << 0, key_pressed, &params);
	mlx_hook(params.mlx.win_ptr, KEY_RELEASED, 1L << 0, key_released, &params);
	mlx_loop(params.mlx.mlx_ptr);
	return (0);
}
