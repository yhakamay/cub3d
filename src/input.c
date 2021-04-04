/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:49:23 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/15 13:49:24 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

int			key_pressed(int keycode, t_params *params)
{
	if (keycode == KEY_ESC)
		exit_game();
	if (keycode == KEY_W)
		params->player.walk_direction_vert = 1;
	else if (keycode == KEY_S)
		params->player.walk_direction_vert = -1;
	else if (keycode == KEY_D)
		params->player.walk_direction_horz = 1;
	else if (keycode == KEY_A)
		params->player.walk_direction_horz = -1;
	else if (keycode == KEY_ARROW_LEFT)
		params->player.turn_direction = 1;
	else if (keycode == KEY_ARROW_RIGHT)
		params->player.turn_direction = -1;
	else
		return (1);
	move_player(&params->player, &params->map);
	render_everything(params);
	return (1);
}

int			key_released(int keycode, t_params *params)
{
	if (keycode == KEY_W)
		params->player.walk_direction_vert = 0;
	else if (keycode == KEY_S)
		params->player.walk_direction_vert = 0;
	else if (keycode == KEY_D)
		params->player.walk_direction_horz = 0;
	else if (keycode == KEY_A)
		params->player.walk_direction_horz = 0;
	else if (keycode == KEY_ARROW_LEFT)
		params->player.turn_direction = 0;
	else if (keycode == KEY_ARROW_RIGHT)
		params->player.turn_direction = 0;
	else
		return (1);
	move_player(&params->player, &params->map);
	render_everything(params);
	return (1);
}
