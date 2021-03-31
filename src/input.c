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

static void	move_player(t_player *p, t_img *img, t_map *map)
{
	float	move_step_vert;
	float	move_step_horz;
	float	new_p_x;
	float	new_p_y;

	p->rotation_angle += p->turn_direction * p->turn_speed;
	p->rotation_angle = normalize_angle(p->rotation_angle);
	move_step_vert = p->walk_direction_vert * p->walk_speed;
	move_step_horz = p->walk_direction_horz * p->walk_speed;
	new_p_x = roundf(p->x +
				cos(p->rotation_angle) * move_step_vert -
				sin(p->rotation_angle) * move_step_horz);
	new_p_y = roundf(p->y +
				sin(p->rotation_angle) * move_step_vert +
				cos(p->rotation_angle) * move_step_horz);
	if (has_wall_at(new_p_x, new_p_y, map) ||
		has_sprite_at(new_p_x, new_p_y, map))
		return ;
	p->x = new_p_x;
	p->y = new_p_y;
}

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
	move_player(&params->player, &params->img, &params->map);
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
	move_player(&params->player, &params->img, &params->map);
	render_everything(params);
	return (1);
}
