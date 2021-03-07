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

#include "cub3d.h"

void render_player(t_player *player, t_img *img)
{
	int i;
	int j;

	i = params->player.x;
	while (i < params->player.x + params->player.width)
	{
		j = params->player.y;
		while (j < params->player.y + params->player.height)
		{
			// mlx_pixel_put() in mlx lib is SUPER slow, so we have to create our own pixel_put() 😵
			my_mlx_pixel_put(params, i, j, COLOR_R);
			j++;
		}
		i++;
	}
}

void move_player(t_params *params)
{
	int new_player_x;
	int new_player_y;
	int move_step;

	move_step = params->player.walk_direction * params->player.walk_speed;
	new_player_x = params->player.x + cos(params->player.rotation_angle) * move_step;
	new_player_y = params->player.y + sin(params->player.rotation_angle) * move_step;
	params->player.x = new_player_x;
	params->player.y = new_player_y;
	render_player(params, COLOR_R);
}

int process_input(int keycode, t_params *params)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(params->mlx.mlx_ptr, params->mlx.win_ptr);
		exit(0);
	}
	else if (keycode == KEY_W)
		params->player.walk_direction = 1;
	else if (keycode == KEY_S)
		params->player.walk_direction = -1;
	else if (keycode == KEY_D)
		params->player.turn_direction = 1;
	else if (keycode == KEY_A)
		params->player.turn_direction = -1;
	move_player(params);
	return (1);
}

int main(void)
{
	t_params params;

	setvbuf(stdout, (char *)NULL, _IONBF, 0);

	params.mlx.mlx_ptr = mlx_init();
	params.mlx.win_ptr = mlx_new_window(params.mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	init_player(&params);
	printf("params.player.x: %d\n", params.player.x);
	printf("params.player.y: %d\n", params.player.y);
	params.img.img = mlx_new_image(params.mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	params.img.addr = mlx_get_data_addr(params.img.img, &params.img.bits_per_pixel, &params.img.line_length, &params.img.endian);
	render_player(&params, COLOR_R);
	mlx_put_image_to_window(params.mlx.mlx_ptr, params.mlx.win_ptr, params.img.img, 0, 0);
	// the second/third params of mlx_hook() ('2' and '1L<<0') are confusing, I don't understand them 🤔
	mlx_hook(params.mlx.win_ptr, 2, 1L << 0, &process_input, &params);
	mlx_loop(params.mlx.mlx_ptr);

	return (0);
}
