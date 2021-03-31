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

static bool	is_player(t_params *params, char c)
{
	if (c == 'N')
		params->player.rotation_angle = 1.5 * PI;
	else if (c == 'S')
		params->player.rotation_angle = 0.5 * PI;
	else if (c == 'E')
		params->player.rotation_angle = 0;
	else if (c == 'W')
		params->player.rotation_angle = PI;
	else
		return (false);
	return (true);
}

static bool	is_sprite(char c)
{
	return (c == '2');
}

static bool	is_forbidden_char(char c)
{
	if (c >= '0' && c <= '2')
		return (false);
	else if (c == ' ')
		return (false);
	else
		return (true);
}

int			check_map_is_closed(t_map *map, int x, int y)
{
	int	ret;

	if (x < 0 || x > 200 || y < 0 || y > 200)
		return (1);
	else if (map->reached[y][x] == true)
		return (0);
	map->reached[y][x] = true;
	if (map->grid[y][x] == '1')
		return (0);
	else if (map->grid[y][x] == '\0')
		return (1);
	ret = 0;
	ret += check_map_is_closed(map, x + 1, y);
	ret += check_map_is_closed(map, x - 1, y);
	ret += check_map_is_closed(map, x, y + 1);
	ret += check_map_is_closed(map, x, y - 1);
	return (ret);
}

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

static void	check_all_path(t_params *params)
{
	params->texture.north.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr, params->map.north_pass, &params->texture.north.width, &params->texture.north.height);
	params->texture.south.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr, params->map.south_pass, &params->texture.south.width, &params->texture.south.height);
	params->texture.west.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr, params->map.west_pass, &params->texture.west.width, &params->texture.west.height);
	params->texture.east.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr, params->map.east_pass, &params->texture.east.width, &params->texture.east.height);
	params->texture.sprite.img = mlx_xpm_file_to_image(params->mlx.mlx_ptr, params->map.sprite_pass, &params->texture.sprite.width, &params->texture.sprite.height);
	if (params->texture.north.img == NULL || params->texture.south.img == NULL || params->texture.west.img == NULL || params->texture.east.img == NULL || params->texture.sprite.img == NULL)
		cub_file_err();
	params->texture.north.addr = mlx_get_data_addr(params->texture.north.img, &params->texture.north.bits_per_pixel, &params->texture.north.line_length, &params->texture.north.endian);
	params->texture.south.addr = mlx_get_data_addr(params->texture.south.img, &params->texture.south.bits_per_pixel, &params->texture.south.line_length, &params->texture.south.endian);
	params->texture.west.addr = mlx_get_data_addr(params->texture.west.img, &params->texture.west.bits_per_pixel, &params->texture.west.line_length, &params->texture.west.endian);
	params->texture.east.addr = mlx_get_data_addr(params->texture.east.img, &params->texture.east.bits_per_pixel, &params->texture.east.line_length, &params->texture.east.endian);
	params->texture.sprite.addr = mlx_get_data_addr(params->texture.sprite.img, &params->texture.sprite.bits_per_pixel, &params->texture.sprite.line_length, &params->texture.sprite.endian);
}

void		check_map(t_params *params)
{
	int tile_index_x;
	int tile_index_y;

	check_all_path(params);
	check_map_info(params);
	locate_sprites(&params->map, &params->sprites);
	tile_index_x = floor(params->player.x / TILE_SIZE);
	tile_index_y = floor(params->player.y / TILE_SIZE);
	if (check_map_is_closed(&params->map, tile_index_x, tile_index_y))
		cub_file_err();
}
