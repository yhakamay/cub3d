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

void draw_pixel(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void render_rect(int x, int y, int width, int height, int color, t_img *img)
{
	int x_i;
	int y_i;

	x_i = x;
	while (x_i < x + width)
	{
		y_i = y;
		while (y_i < y + height)
		{
			draw_pixel(img, x_i, y_i, color);
			y_i++;
		}
		x_i++;
	}
}

void render_line(t_img *img, int x1, int y1, int x2, int y2, int color)
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
		draw_pixel(img, x1 + (int)(x_delta * i), y1 + (int)(y_delta * i), color);
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
	t_ray rays[g_num_rays];

	ray_angle = player->rotation_angle - (FOV_ANGLE * 0.5);
	i = 0;
	while (i < g_num_rays)
	{
		rays[i] = cast_ray(params, player, normalize_angle(ray_angle));
		render_line(img, player->x, player->y, rays[i].wall_hit_x, rays[i].wall_hit_y, PLAYER_COLOR);
		ray_angle += FOV_ANGLE / g_num_rays;
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
			tile_color = params->map.grid[i][j] != '0' ? COLOR_WHITE : COLOR_LIGHT_GRAY;
			render_rect(x * MINIMAP_SCALE_FACTOR, y * MINIMAP_SCALE_FACTOR, TILE_SIZE * MINIMAP_SCALE_FACTOR, TILE_SIZE * MINIMAP_SCALE_FACTOR, tile_color, &params->img);
			j++;
		}
		i++;
	}
}

static void	render_texture(t_params *params, t_img *img, t_ray *ray, int x, int height)
{
	char		*color_addr;
	float		col;
	int			i;
	int			j;

	col = ray->length_from_leftside * height / TILE_SIZE;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < g_wall_strip_width)
		{
			color_addr = img->addr + (int)roundf(i * img->height / height) * img->line_length + (int)roundf((col + j) * img->width / height) * (img->bits_per_pixel / 8);
			if (params->map.window_height / 2 - height / 2 + i >= 0 && params->map.window_height / 2 - height / 2 + i <= params->map.window_height)
			{
				draw_pixel(&params->img, x, params->map.window_height / 2 - height / 2 + i, *(int *)(color_addr));
			}
			j++;
		}
		i++;
	}
}

static void	render_texture_reverse(t_params *params, t_img *img, t_ray *ray, int x, int height)
{
	char		*color_addr;
	float		col;
	int			i;
	int			j;

	col = ray->length_from_leftside * height/ TILE_SIZE;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < g_wall_strip_width)
		{
			color_addr = img->addr + ((int)roundf(i * img->height / height) + 1) * img->line_length - (int)roundf((col + j) * img->width / height + 1) * (img->bits_per_pixel / 8);
			if (params->map.window_height / 2 - height / 2 + i >= 0 && params->map.window_height / 2 - height / 2 + i <= params->map.window_height)
			{
				draw_pixel(&params->img, x, params->map.window_height / 2 - height / 2 + i, *(unsigned int *)(color_addr));
			}
			j++;
		}
		i++;
	}
}

static void	render_texture_sprite(t_params *params, t_img *img, t_ray *ray, int x, int height)
{
	char		*color_addr;
	int			color;
	float		col;
	int			i;
	int			j;

	col = ray->length_from_leftside * height / TILE_SIZE;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < g_wall_strip_width)
		{
			color_addr = img->addr + (int)roundf(i * img->height / height) * img->line_length + (int)roundf((col + j) * img->width / height) * (img->bits_per_pixel / 8);
			color = *(int *)color_addr;
			if (color != 0)
			{
				draw_pixel(&params->img, x, params->map.window_height / 2 - height / 2 + i, *(int *)(color_addr));
			}
			j++;
		}
		i++;
	}
}


static void render_3d_wall(t_params *params, t_player *player, t_map *map, t_img *img)
{
	int i;
	int wall_strip_height;
	float correct_wall_distance;
	float distance_to_plane;
	float ray_angle;
	t_ray ray;

	ray_angle = normalize_angle(player->rotation_angle - (FOV_ANGLE * 0.5));
	i = 0;
	while (i < g_num_rays)
	{
		ray = cast_ray(params, player, ray_angle);
		correct_wall_distance = ray.distance * cos(ray.ray_angle - player->rotation_angle);
		distance_to_plane = (map->window_width / 2) / tan(FOV_ANGLE / 2);
		wall_strip_height = (TILE_SIZE / correct_wall_distance) * distance_to_plane;
		if (ray.was_hit_vertical == true && (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI))
		{
			//west wall
			render_texture_reverse(params, &params->texture.west, &ray, i * g_wall_strip_width, wall_strip_height);
		}
		else if (ray.was_hit_vertical == true && (ray_angle >= 0.5 * PI && ray_angle <= 1.5 * PI))
		{
			//east wall
			render_texture(params, &params->texture.east, &ray, i * g_wall_strip_width, wall_strip_height);
		}
		else if (ray.was_hit_vertical == false && (ray_angle >= 0 && ray_angle < PI))
		{
			//north wall
			render_texture(params, &params->texture.north, &ray, i * g_wall_strip_width, wall_strip_height);
		}
		else if (ray.was_hit_vertical == false && (ray_angle >= PI && ray_angle < 2 * PI))
		{
			//south wall
			render_texture_reverse(params, &params->texture.south, &ray, i * g_wall_strip_width, wall_strip_height);
		}
		ray_angle = normalize_angle(ray_angle + FOV_ANGLE / g_num_rays);
		i++;
	}
}

void render_everything(t_params *params)
{
	render_sky(&params->img, &params->map);
	render_floor(&params->img, &params->map);
	render_3d_wall(params, &params->player, &params->map, &params->img);
	render_sprite(params, &params->player, &params->map, &params->img);
	render_minimap(params);
	render_player(&params->player, &params->img);
	render_rays(params, &params->player, &params->img);
	mlx_put_image_to_window(params->mlx.mlx_ptr, params->mlx.win_ptr, params->img.img, 0, 0);
}
