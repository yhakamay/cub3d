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

static void	render_texture(t_params *params, t_img *img, t_ray *ray, int x, int height)
{
	char	*color_addr;
	float	col;
	int		i;
	int		j;

	col = ray->length_from_leftside * height / TILE_SIZE;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < g_wall_strip_width)
		{
			color_addr = img->addr + (int)roundf(i * img->height / height) *
				img->line_length + (int)roundf((col + j) *
				img->width / height) *
				(img->bits_per_pixel / 8);
			if (params->map.window_height / 2 - height / 2 + i >= 0 &&
				params->map.window_height / 2 - height / 2 + i < params->map.window_height)
			{
				draw_pixel(
					&params->img,
					x,
					params->map.window_height / 2 - height / 2 + i,
					*(int *)(color_addr));
			}
			j++;
		}
		i++;
	}
}

static void	render_texture_reverse(t_params *params, t_img *img, t_ray *ray, int x, int height)
{
	char	*color_addr;
	float	col;
	int		i;
	int		j;

	col = ray->length_from_leftside * height / TILE_SIZE;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < g_wall_strip_width)
		{
			color_addr = img->addr + ((int)roundf(i * img->height / height) + 1) *
				img->line_length - (int)roundf((col + j) *
				img->width / height + 1) *
				(img->bits_per_pixel / 8);
			if (params->map.window_height / 2 - height / 2 + i >= 0 &&
				params->map.window_height / 2 - height / 2 + i < params->map.window_height)
			{
				draw_pixel(
					&params->img,
					x,
					params->map.window_height / 2 - height / 2 + i,
					*(unsigned int *)(color_addr));
			}
		}
	}
}

static void	render_3d_wall(t_params *params, t_player *p, t_texture *texture, t_map *map)
{
	int		i;
	int		wall_strip_height;
	float	correct_wall_distance;
	float	distance_to_plane;
	float	ray_angle;

	params->rays = (t_ray *)malloc(sizeof(t_ray) * g_num_rays);
	ray_angle = normalize_angle(p->rotation_angle - (FOV_ANGLE * 0.5));
	i = -1;
	while (++i < g_num_rays)
	{
		params->rays[i] = cast_ray(params, p, ray_angle);
		correct_wall_distance = params->rays[i].distance *
			cos(params->rays[i].ray_angle - p->rotation_angle);
		correct_wall_distance = correct_wall_distance == 0 ?
			3 : correct_wall_distance;
		distance_to_plane = (map->window_width / 2) / tan(FOV_ANGLE / 2);
		wall_strip_height = (TILE_SIZE / correct_wall_distance) * distance_to_plane;
		if (params->rays[i].was_hit_vertical == true &&
			(ray_angle < 0.5 * PI || ray_angle > 1.5 * PI))
			render_texture_reverse(params, &texture->west, &params->rays[i],
				i * g_wall_strip_width, wall_strip_height);
		else if (params->rays[i].was_hit_vertical == true &&
			(ray_angle >= 0.5 * PI && ray_angle <= 1.5 * PI))
			render_texture(params, &texture->east, &params->rays[i],
				i * g_wall_strip_width, wall_strip_height);
		else if (params->rays[i].was_hit_vertical == false &&
			(ray_angle >= 0 && ray_angle < PI))
			render_texture(params, &texture->north, &params->rays[i],
				i * g_wall_strip_width, wall_strip_height);
		else if (params->rays[i].was_hit_vertical == false &&
			(ray_angle >= PI && ray_angle < 2 * PI))
			render_texture_reverse(params, &texture->south,
				&params->rays[i], i * g_wall_strip_width, wall_strip_height);
		ray_angle = normalize_angle(ray_angle + FOV_ANGLE / g_num_rays);
	}
}

void		render_everything(t_params *params)
{
	render_ceiling(&params->img, &params->map);
	render_floor(&params->img, &params->map);
	render_3d_wall(params, &params->player, &params->texture, &params->map);
	render_sprites(params);
	mlx_put_image_to_window(
		params->mlx.mlx_ptr,
		params->mlx.win_ptr,
		params->img.img,
		0,
		0);
}
