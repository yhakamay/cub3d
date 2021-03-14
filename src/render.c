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

static void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void render_rect(int x, int y, int width, int height, int color, t_img *img)
{
	int x_i;
	int y_i;

	x_i = x;
	while (x_i < x + width)
	{
		y_i = y;
		while (y_i < y + height)
		{
			my_mlx_pixel_put(img, x_i, y_i, color);
			y_i++;
		}
		x_i++;
	}
}

static void render_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	double x_delta;
	double y_delta;
	double len;
	int i;

	x_delta = x2 - x1;
	y_delta = y2 - y1;
	len = (fabs(x_delta) >= fabs(y_delta)) ? fabs(x_delta) : fabs(y_delta);
	x_delta /= len;
	y_delta /= len;
	i = 0;
	while (i < (int)len)
	{
		my_mlx_pixel_put(img, x1 + (int)(x_delta * i), y1 + (int)(y_delta * i), color);
		i++;
	}
}

static void render_sky(t_img *img, t_map *map)
{
	render_rect(0, 0, map->window_width, map->window_height / 2, COLOR_CYAN, img);
}

static void render_floor(t_img *img, t_map *map)
{
	render_rect(0, map->window_height / 2, map->window_width, map->window_height / 2, COLOR_GRAY, img);
}

static void render_rays(t_params *params, t_player *player, t_img *img)
{
	int i;
	float ray_angle;
	t_ray rays[NUM_RAYS];

	ray_angle = player->rotation_angle - (FOV_ANGLE * 0.5);
	i = 0;
	while (i < NUM_RAYS)
	{
		rays[i] = cast_ray(params, player, normalize_angle(ray_angle));
		render_line(img, player->x, player->y, rays[i].wall_hit_x, rays[i].wall_hit_y, PLAYER_COLOR);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}

static void render_player(t_player *player, t_img *img)
{
	render_rect(
		player->x,
		player->y,
		player->width * MINIMAP_SCALE_FACTOR,
		player->height * MINIMAP_SCALE_FACTOR,
		player->color,
		img);
}

static void render_minimap(t_params *params)
{
	int i;
	int j;
	int x;
	int y;
	int tile_color;

	i = 0;
	while (params->map.grid[i][0] != '\0')
	{
		j = 0;
		while (params->map.grid[i][j] != '\0')
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			tile_color = params->map.grid[i][j] != '0' ? COLOR_YELLOW : COLOR_GRAY;
			render_rect(x * MINIMAP_SCALE_FACTOR, y * MINIMAP_SCALE_FACTOR, TILE_SIZE * MINIMAP_SCALE_FACTOR, TILE_SIZE * MINIMAP_SCALE_FACTOR, tile_color, &params->img);
			j++;
		}
		i++;
	}
}

static void render_3d_wall(t_params *params, t_player *player, t_map *map, t_img *img)
{
	int i;
	int wall_strip_width;
	int wall_strip_height;
	float correct_wall_distance;
	float distance_to_plane;
	float ray_angle;
	t_ray ray;

	ray_angle = player->rotation_angle - (FOV_ANGLE * 0.5);
	wall_strip_width = map->window_width / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray = cast_ray(params, player, normalize_angle(ray_angle));
		correct_wall_distance = ray.distance * cos(ray.ray_angle - player->rotation_angle);
		distance_to_plane = (map->window_width / 2) / tan(FOV_ANGLE / 2);
		wall_strip_height = (TILE_SIZE / correct_wall_distance) * distance_to_plane;
		wall_strip_height = wall_strip_height > map->window_height ? map->window_height : wall_strip_height;
		render_rect(i * wall_strip_width,
					(map->window_height / 2) - (wall_strip_height / 2),
					wall_strip_width,
					wall_strip_height,
					COLOR_WHITE,
					img);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}

void render_everything(t_params *params)
{
	render_sky(&params->img, &params->map);
	render_floor(&params->img, &params->map);
	render_3d_wall(params, &params->player, &params->map, &params->img);
	render_minimap(params);
	render_player(&params->player, &params->img);
	render_rays(params, &params->player, &params->img);
	mlx_put_image_to_window(params->mlx.mlx_ptr, params->mlx.win_ptr, params->img.img, 0, 0);
}
