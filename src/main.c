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

// handles key input and used by mlx_hool()
int	process_input(int keycode, t_params *params)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(params->mlx_ptr, params->win_ptr);
		exit(0);
	}
	if (keycode == KEY_A)
		printf("A\n");
	if (keycode == KEY_S)
		printf("S\n");
	if (keycode == KEY_D)
		printf("D\n");
	if (keycode == KEY_W)
		printf("W\n");
	return (1);
}

int	main()
{
	t_params params;

	// mlx_init() is always needed if you use mlx lib
	params.mlx_ptr = mlx_init();
	// create a new window
	params.win_ptr = mlx_new_window(params.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	// the second/third params are confusing, I don't understand them 🤔
	mlx_hook(params.win_ptr, 2, 1L<<0, &process_input, &params);
	// keep the program running
	mlx_loop(params.mlx_ptr);

	return (0);
}
