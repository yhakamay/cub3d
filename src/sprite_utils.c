/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:19:35 by yhakamay          #+#    #+#             */
/*   Updated: 2021/04/02 13:19:38 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

void	normalize_p_sprite_angle(float *p_sprite_angle, t_player *p)
{
	if (*p_sprite_angle < 0)
		*p_sprite_angle *= -1;
	else
		*p_sprite_angle = 2 * PI - *p_sprite_angle;
	*p_sprite_angle -= p->rotation_angle;
	if (*p_sprite_angle > PI)
		*p_sprite_angle -= 2 * PI;
	else if (*p_sprite_angle < -PI)
		*p_sprite_angle += 2 * PI;
}

bool	is_inside_fov(t_params *params, int height, int x,
	int i, int j)
{
	return (params->map.window_height / 2 - height / 2 + i >= 0 &&
			params->map.window_height / 2 - height / 2 + i <
				params->map.window_height &&
			x + j >= 0 && x + j < params->map.window_width);
}

int		calculate_left_end_x(t_params *params, float distance_to_plane,
	int i, int wall_strip_height)
{
	int left_end_x;

	left_end_x = params->map.window_width / 2 +
					distance_to_plane * tan(params->sprites[i].angle) -
					wall_strip_height / 2;
	return (left_end_x);
}

char	*calculate_color_addr(t_texture *texture, int height, int i, int j)
{
	char *color_addr;

	color_addr = texture->sprite.addr + (int)roundf(
		i * texture->sprite.height / height) * texture->sprite.line_length +
		(int)roundf(j * texture->sprite.width / height) *
		(texture->sprite.bits_per_pixel / 8);
	return (color_addr);
}
