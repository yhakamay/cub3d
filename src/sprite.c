/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:21:46 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/26 21:21:47 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

static void	check_visible_sprites(t_params *params, t_player *p,
	t_sprite *sprites)
{
	int		i;
	float	p_sprite_angle;

	i = -1;
	while (++i < g_num_sprites)
	{
		sprites[i].distance = get_distance(
			p->x, p->y,
			sprites[i].x, sprites[i].y);
		p_sprite_angle = atan2(
			-(sprites[i].y - p->y),
			sprites[i].x - p->x);
		normalize_p_sprite_angle(&p_sprite_angle, p);
		sprites[i].angle = p_sprite_angle;
		p_sprite_angle = fabs(p_sprite_angle);
		sprites[i].visible = p_sprite_angle <= (float)(FOV_ANGLE / 2) + 0.2 ?
			true : false;
	}
}

static void	sort_sprites(t_params *params)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = -1;
	while (++i < g_num_sprites - 1)
	{
		j = g_num_sprites;
		while (--j > i)
		{
			if (params->sprites[j - 1].distance < params->sprites[j].distance)
			{
				temp = params->sprites[j];
				params->sprites[j] = params->sprites[j - 1];
				params->sprites[j - 1] = temp;
			}
		}
	}
}

static void	render_one_sprite(t_params *params, t_sprite *sprite,
	int x, int height)
{
	char	*color_addr;
	int		color;
	float	col;
	int		i;
	int		j;

	col = 0;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < height)
		{
			color_addr = calculate_color_addr(&params->texture, height, i, j);
			color = *(int *)color_addr;
			if (is_inside_fov(&params->map, height, i) &&
				x + j >= 0 && x + j < params->map.window_width &&
				sprite->distance < params->rays[x + j].distance &&
				color != 0)
				draw_pixel(&params->img, x + j,
					params->map.window_height / 2 - height / 2 + i,
					*(int *)(color_addr));
		}
	}
}

void		render_sprites(t_params *params)
{
	int		i;
	int		left_end_x;
	int		wall_strip_height;
	float	correct_wall_distance;
	float	distance_to_plane;

	i = -1;
	check_visible_sprites(params, &params->player, params->sprites);
	sort_sprites(params);
	while (++i < g_num_sprites)
	{
		if (!params->sprites[i].visible)
			continue ;
		correct_wall_distance = params->sprites[i].distance *
								cos(params->sprites[i].angle);
		distance_to_plane = (params->map.window_width / 2) / tan(FOV_ANGLE / 2);
		wall_strip_height = (TILE_SIZE / correct_wall_distance) *
								distance_to_plane;
		left_end_x = calculate_left_end_x(params, distance_to_plane,
						i, wall_strip_height);
		render_one_sprite(params, &params->sprites[i],
			left_end_x, wall_strip_height);
	}
}
