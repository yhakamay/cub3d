/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:11:50 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/19 10:11:52 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

void		get_wall_texture(t_map *map, char *line, int i, int *obj_num)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
		get_north_path(line, i, map);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		get_south_path(line, i, map);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		get_west_path(line, i, map);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		get_east_path(line, i, map);
	(*obj_num)++;
}

void		get_floor_texture(t_map *map, char *line, int i, int j)
{
	int count;

	i += 1 + num_of_spaces(line, i + 1);
	while (j < 3)
	{
		count = num_of_numbers(line, i);
		if (count > 3 || count == 0)
			cub_file_err();
		map->floor_rgb[j] = ft_atoi(line + i);
		if (map->floor_rgb[j] > 255)
			cub_file_err();
		i += count;
		if (j == 2)
			break ;
		else if (line[i] != ',')
			cub_file_err();
		i++;
		j++;
	}
	if (ft_strlen(line + i) != (size_t)num_of_spaces(line, i))
		cub_file_err();
}

void		get_ceiling_texture(t_map *map, char *line, int i, int j)
{
	int count;

	i += 1 + num_of_spaces(line, i + 1);
	while (j < 3)
	{
		count = num_of_numbers(line, i);
		if (count > 3 || count == 0)
			cub_file_err();
		map->ceiling_rgb[j] = ft_atoi(line + i);
		if (map->ceiling_rgb[j] > 255)
			cub_file_err();
		i += count;
		if (j == 2)
			break ;
		else if (line[i] != ',')
			cub_file_err();
		i++;
		j++;
	}
	if (ft_strlen(line + i) != (size_t)num_of_spaces(line, i))
		cub_file_err();
}

void		get_sprite_texture(t_map *map, char *line, int i, int *obj_num)
{
	i++;
	if (line[i] != ' ')
		cub_file_err();
	map->sprite_pass = ft_strtrim(line + i, " ");
	if (!(is_valid_path(line, map->sprite_pass, i)))
		cub_file_err();
	(*obj_num)++;
}
