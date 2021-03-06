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


void		create_minimap()
{
	// TODO: create a minimap
	int	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
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
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
}

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void		render_player(t_data img, int x, int y, int width, int height, int color)
{
	int	i;
	int	j;

	i = x;
	while (i < x + width)
	{
		j = y;
		while (j < y + height)
		{
			// mlx_pixel_put() in mlx lib is SUPER slow, so we have to create our own pixel_put() 😵
			my_mlx_pixel_put(&img, i, j, COLOR_R);
			j++;
		}
		i++;
	}
}

void		init_player(t_params *params)
{
	params->player_x = WINDOW_WIDTH / 2;
	params->player_y = WINDOW_HEIGHT / 2;
	params->player_width = 20;
	params->player_height = 20;
	params->player_turn_direction = 0;
	params->player_walk_direction = 0;
	params->player_rotation_angle = PI / 2;
	params->player_walk_speed = 200;
	params->player_turn_speed = 90 * (PI / 180);
}

void		move_player(t_params params, int walk_direction, int turn_direciton)
{
}

int			process_input(int keycode, t_params *params)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(params->mlx_ptr, params->win_ptr);
		exit(0);
	}

	if (keycode == KEY_W)
		params->player_walk_direction = 1;
	else if (keycode == KEY_S)
		params->player_walk_direction = -1;
	else if (keycode == KEY_D)
		params->player_turn_direction = 1;
	else if (keycode == KEY_A)
		params->player_turn_direction = -1;
	printf("params.player_walk_direction:\t%d\n", params->player_walk_direction);
	printf("params.player_turn_direction:\t%d\n", params->player_turn_direction);
	return (1);
}

int			main(void)
{
	t_params	params;
    t_data		img;

	setvbuf(stdout, (char *)NULL, _IONBF, 0);

    params.mlx_ptr = mlx_init();
	params.win_ptr = mlx_new_window(params.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	init_player(&params);
    img.img = mlx_new_image(params.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	render_player(img, params.player_x, params.player_y, params.player_width, params.player_height, COLOR_R);
    mlx_put_image_to_window(params.mlx_ptr, params.win_ptr, img.img, 0, 0);
	// the second/third params of mlx_hook() ('2' and '1L<<0') are confusing, I don't understand them 🤔
	mlx_hook(params.win_ptr, 2, 1L<<0, &process_input, &params);
    mlx_loop(params.mlx_ptr);

	return (0);
}
