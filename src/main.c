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

	i = player->x;
	while (i < player->x + player->width)
	{
		j = player->y;
		while (j < player->y + player->height)
		{
			// mlx_pixel_put() in mlx lib is SUPER slow, so we have to create our own pixel_put() 😵
			my_mlx_pixel_put(img, i, j, player->color);
			j++;
		}
		i++;
	}
}

void render(t_params *params)
{
	render_player(&params->player, &params->img);

	// two functions below are coming soon...
	// render_minimap;
	// render_view;

	mlx_put_image_to_window(params->mlx.mlx_ptr, params->mlx.win_ptr, params->img.img, 0, 0);
}

void move_player(t_player *player, t_img *img)
{
	int new_player_x;
	int new_player_y;
	int move_step;

	move_step = player->walk_direction * player->walk_speed;
	new_player_x = player->x + cos(player->rotation_angle) * move_step;
	new_player_y = player->y + sin(player->rotation_angle) * move_step;
	player->x = new_player_x;
	player->y = new_player_y;
	//render_player(player, img, COLOR_R);
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

	// change the parameter of t_player and render them
	move_player(&params->player, &params->img);
	render(params);

	return (1);
}

int main(void)
{
	t_params params;

	// init some info
	params.mlx.mlx_ptr = mlx_init();
	params.mlx.win_ptr = mlx_new_window(params.mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	init_player(&params.player);

	// create a image on the window
	params.img.img = mlx_new_image(params.mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	params.img.addr = mlx_get_data_addr(params.img.img, &params.img.bits_per_pixel, &params.img.line_length, &params.img.endian);

	// render a player and push the image to window
	render_player(&params.player, &params.img);
	mlx_put_image_to_window(params.mlx.mlx_ptr, params.mlx.win_ptr, params.img.img, 0, 0);

	// accept key input and call some function via process_input()
	mlx_hook(params.mlx.win_ptr, 2, 1L << 0, &process_input, &params);

	// make the game continuous
	mlx_loop(params.mlx.mlx_ptr);

	return (0);
}
