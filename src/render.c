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

void render_everything(t_params *params)
{
	refresh_img(&params->img, &params->map);

	render_minimap(params);
	render_player(&params->player, &params->img);
	render_rays(params, &params->player, &params->img);

	mlx_put_image_to_window(params->mlx.mlx_ptr, params->mlx.win_ptr, params->img.img, 0, 0);
}

void render_minimap(t_params *params)
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
			tile_color = params->map.grid[i][j] != '0' ? 111 : 0;

			render_rect(x * MINIMAP_SCALE_FACTOR, y * MINIMAP_SCALE_FACTOR, TILE_SIZE * MINIMAP_SCALE_FACTOR, TILE_SIZE * MINIMAP_SCALE_FACTOR, tile_color, &params->img);
			j++;
		}
		i++;
	}
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
			my_mlx_pixel_put(img, x_i, y_i, color);
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
		my_mlx_pixel_put(img, x1 + (int)(x_delta * i), y1 + (int)(y_delta * i), color);
		i++;
	}
}

void render_rays(t_params *params, t_player *player, t_img *img)
{
    int i;
    t_ray *rays;

    if (!(rays = malloc(sizeof(t_ray) * NUM_RAYS)))
        return;
    i = 0;
    while (i < NUM_RAYS)
    {
        rays[i] = cast_ray(params, player, player->rotation_angle - FOV_ANGLE * (0.5 - i / (float)(params->map.window_width)));
        render_line(img, player->x * MINIMAP_SCALE_FACTOR, player->y * MINIMAP_SCALE_FACTOR, rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR, rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR, PLAYER_COLOR);
        i++;
    }
    free(rays);
}

void render_player(t_player *player, t_img *img)
{
	render_rect(
		player->x,
		player->y,
		player->width * MINIMAP_SCALE_FACTOR,
		player->height * MINIMAP_SCALE_FACTOR,
		player->color,
		img);
	// render_line(player->x,
	// 			player->y,
	// 			player->rotation_angle,
	// 			PLAYER_RAY_LENGTH,
	// 			player->color,
	// 			img);
}

// old version of render_line() which requires rotation_angle
// it doesn't work to cast rays, so created new version above
// void render_line(int x_start, int y_start, float rotaion_angle, int length, int color, t_img *img)
// {
// 	int x_end;
// 	int y_end;
// 	int x_sign;
// 	int x_delta;
// 	int x_base_len;
// 	int i;

// 	x_end = x_start + cos(rotaion_angle) * length;
// 	y_end = y_start + sin(rotaion_angle) * length;

// 	x_delta = x_end - x_start;
// 	x_sign = x_delta < 0 ? -1 : 1;
// 	x_base_len = abs(x_delta);

// 	i = 0;
// 	while (i < x_base_len)
// 	{
// 		my_mlx_pixel_put(img, x_start + (i * x_sign), y_start + (tan(rotaion_angle) * i * x_sign), color);
// 		i++;
// 	}
// }
