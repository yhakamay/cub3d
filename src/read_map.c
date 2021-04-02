/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuki <matsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:16:37 by matsuki           #+#    #+#             */
/*   Updated: 2021/03/14 11:37:30 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

static void	check_obj(t_map *map, char *line, int *obj_num)
{
	int	i;

	i = 0;
	i += num_of_spaces(line, i);
	if (line[i] == 'R')
		get_resolution(map, line, i, obj_num);
	else if ((line[i] == 'N' && line[i + 1] == 'O') ||
				(line[i] == 'S' && line[i + 1] == 'O') ||
				(line[i] == 'W' && line[i + 1] == 'E') ||
				(line[i] == 'E' && line[i + 1] == 'A'))
		get_wall_texture(map, line, i, obj_num);
	else if (line[i] == 'S')
		get_sprite_texture(map, line, i, obj_num);
	else if (line[i] == 'F')
	{
		get_floor_texture(map, line, i, 0);
		(*obj_num)++;
	}
	else if (line[i] == 'C')
	{
		get_ceiling_texture(map, line, i, 0);
		(*obj_num)++;
	}
}

static void	offset_map(t_map *map)
{
	map->window_width = 0;
	map->window_height = 0;
	map->floor_rgb[0] = 0;
	map->floor_rgb[1] = 0;
	map->floor_rgb[2] = 0;
	map->ceiling_rgb[0] = 0;
	map->ceiling_rgb[1] = 0;
	map->ceiling_rgb[2] = 0;
	ft_memset(map->grid, 0, 200 * 201);
	ft_memset(map->reached, false, 200 * 200);
}

static void	make_map(t_map *map, char *line, int *obj_num)
{
	static int	i;
	int			len;

	len = ft_strlen(line);
	if (len == 0)
	{
		(*obj_num)++;
		return ;
	}
	else if (len > 200 || i > 200)
		cub_file_err();
	ft_memcpy(map->grid[i], line, len + 1);
	i++;
}

void		read_map(char *file_path, t_map *map)
{
	char	*line;
	int		fd;
	int		obj_num;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		no_file_err();
	obj_num = 0;
	offset_map(map);
	while (get_next_line(fd, &line))
	{
		if (obj_num < 8)
			check_obj(map, line, &obj_num);
		else if (obj_num == 8)
			make_map(map, line, &obj_num);
		else
		{
			free(line);
			cub_file_err();
		}
		free(line);
	}
	make_map(map, line, &obj_num);
	free(line);
}
