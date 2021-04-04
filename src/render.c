/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:35:18 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/12 11:35:20 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

static void	render_3d_wall(t_params *params, t_player *p, t_map *map)
{
	int		i;
	int		wall_strip_height;
	float	correct_wall_distance;
	float	ray_angle;

	params->rays = (t_ray *)malloc(sizeof(t_ray) * g_num_rays);
	ray_angle = normalize_angle(p->rotation_angle - (FOV_ANGLE / 2));
	i = -1;
	while (++i < g_num_rays)
	{
		params->rays[i] = cast_ray(params, p, ray_angle);
		correct_wall_distance = params->rays[i].distance *
			cos(params->rays[i].ray_angle - p->rotation_angle);
		correct_wall_distance = correct_wall_distance == 0 ?
			3 : correct_wall_distance;
		wall_strip_height = (TILE_SIZE / correct_wall_distance) *
							(map->window_width / 2) / tan(FOV_ANGLE / 2);
		render_walls(params, i, wall_strip_height, ray_angle);
		ray_angle = normalize_angle(ray_angle + FOV_ANGLE / g_num_rays);
	}
}

void		render_everything(t_params *params)
{
	render_ceiling(&params->img, &params->map);
	render_floor(&params->img, &params->map);
	render_3d_wall(params, &params->player, &params->map);
	render_sprites(params);
	mlx_put_image_to_window(
		params->mlx.mlx_ptr,
		params->mlx.win_ptr,
		params->img.img,
		0,
		0);
}
