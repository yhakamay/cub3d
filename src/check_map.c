/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuki <matsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:05:20 by matsuki           #+#    #+#             */
/*   Updated: 2021/03/14 14:02:02 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

static void	locate_sprites(t_map *map, t_sprite **sprites)
{
	int	i;
	int	j;
	int	k;

	*sprites = (t_sprite *)malloc(sizeof(t_sprite) * g_num_sprites);
	i = 0;
	k = 0;
	while (map->grid[i][0] != '\0')
	{
		j = 0;
		while (map->grid[i][j] != '\0')
		{
			if (is_sprite(map->grid[i][j]))
			{
				(*sprites)[k].x = (j + 0.5) * TILE_SIZE;
				(*sprites)[k].y = (i + 0.5) * TILE_SIZE;
				k++;
			}
			j++;
		}
		i++;
	}
}

void		check_map_info(t_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (params->map.grid[i][0] != '\0')
	{
		j = 0;
		while (params->map.grid[i][j] != '\0')
		{
			if (is_player(params, params->map.grid[i][j]))
			{
				params->player.x = (j + 0.5) * TILE_SIZE + 1;
				params->player.y = (i + 0.5) * TILE_SIZE + 1;
				params->map.grid[i][j] = '0';
			}
			else if (is_sprite(params->map.grid[i][j]))
				g_num_sprites++;
			else if (is_forbidden_char(params->map.grid[i][j]))
				cub_file_err();
			j++;
		}
		i++;
	}
}

static void	texture_to_image(t_params *params, t_texture *texture)
{
	texture->north.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr,
												params->map.north_pass,
												&texture->north.width,
												&texture->north.height);
	texture->south.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr,
												params->map.south_pass,
												&texture->south.width,
												&texture->south.height);
	texture->west.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr,
												params->map.west_pass,
												&texture->west.width,
												&texture->west.height);
	texture->east.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr,
												params->map.east_pass,
												&texture->east.width,
												&texture->east.height);
	texture->sprite.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr,
												params->map.sprite_pass,
												&texture->sprite.width,
												&texture->sprite.height);
	if (texture->north.img == NULL || texture->south.img == NULL ||
		texture->west.img == NULL || texture->east.img == NULL ||
		texture->sprite.img == NULL)
		cub_file_err();
}

static void	check_all_path(t_params *params, t_texture *texture)
{
	texture_to_image(params, texture);
	texture->north.addr = mlx_get_data_addr(texture->north.img,
											&texture->north.bits_per_pixel,
											&texture->north.line_length,
											&texture->north.endian);
	texture->south.addr = mlx_get_data_addr(texture->south.img,
											&texture->south.bits_per_pixel,
											&texture->south.line_length,
											&texture->south.endian);
	texture->west.addr = mlx_get_data_addr(texture->west.img,
											&texture->west.bits_per_pixel,
											&texture->west.line_length,
											&texture->west.endian);
	texture->east.addr = mlx_get_data_addr(texture->east.img,
											&texture->east.bits_per_pixel,
											&texture->east.line_length,
											&texture->east.endian);
	texture->sprite.addr = mlx_get_data_addr(texture->sprite.img,
											&texture->sprite.bits_per_pixel,
											&texture->sprite.line_length,
											&texture->sprite.endian);
}

void		check_map(t_params *params)
{
	int tile_index_x;
	int tile_index_y;

	check_all_path(params, &params->texture);
	check_map_info(params);
	locate_sprites(&params->map, &params->sprites);
	tile_index_x = floor(params->player.x / TILE_SIZE);
	tile_index_y = floor(params->player.y / TILE_SIZE);
	if (is_map_closed(&params->map, tile_index_x, tile_index_y))
		cub_file_err();
}
