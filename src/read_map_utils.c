/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:24:12 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/20 23:24:13 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

int		num_of_spaces(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] == ' ')
		j++;
	return (j);
}

int		num_of_numbers(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] >= '0' && line[i + j] <= '9')
		j++;
	return (j);
}

void	get_resolution(t_map *map, char *line, int i, int *obj_num)
{
	i++;
	i += num_of_spaces(line, i);
	while (line[i] >= '0' && line[i] <= '9')
	{
		map->window_width = map->window_width * 10 + line[i] - '0';
		i++;
	}
	if (line[i] != ' ')
		cub_file_err();
	i += num_of_spaces(line, i);
	while (line[i] >= '0' && line[i] <= '9')
	{
		map->window_height = map->window_height * 10 + line[i] - '0';
		i++;
	}
	if (ft_strlen(line + i) != num_of_spaces(line, i))
		cub_file_err();
	(*obj_num)++;
}

static bool	is_valid_path(char *line, char *path, int i)
{
	if (ft_strlen(line + i) != ft_strlen(path) + num_of_spaces(line, i))
		return (false);
	return (true);
}

void	get_wall_texture(t_map *map, char *line, int i, int *obj_num)
{
	i += 2;
	if (line[i] != ' ')
		cub_file_err();
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		map->north_pass = ft_strtrim(line + i, " ");
		if (!(is_valid_path(line, map->north_pass, i)))
			cub_file_err();
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		map->south_pass = ft_strtrim(line + i, " ");
		if (!(is_valid_path(line, map->north_pass, i)))
			cub_file_err();
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		map->west_pass = ft_strtrim(line + i, " ");
		if (!(is_valid_path(line, map->west_pass, i)))
			cub_file_err();
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		map->east_pass = ft_strtrim(line + i, " ");
		if (!(is_valid_path(line, map->east_pass, i)))
			cub_file_err();
	}
	(*obj_num)++;
}

void	get_floor_ceiling_texture(t_map *map, char *line, int i, int j, int *obj_num, char f_or_c)
{
	int count;

	i++;
	i += num_of_spaces(line, i);
	while (j < 3)
	{
		count = num_of_numbers(line, i);
		if (count > 3 || count == 0)
			cub_file_err();
		if (f_or_c == 'F')
		{
			map->floor_rgb[j] = ft_atoi(line + i);
			if (map->floor_rgb[j] > 255)
				cub_file_err();
		}
		else
		{
			map->ceiling_rgb[j] = ft_atoi(line + i);
			if (map->ceiling_rgb[j] > 255)
				cub_file_err();
		}
		i += count;
		if (j == 2)
			break ;
		else if (line[i] != ',')
			cub_file_err();
		i++;
		j++;
	}
	if (ft_strlen(line + i) != num_of_spaces(line, i))
		cub_file_err();
	(*obj_num)++;
}

void	get_sprite_texture(t_map *map, char *line, int i, int *obj_num)
{
	i++;
	if (line[i] != ' ')
		cub_file_err();
	map->sprite_pass = ft_strtrim(line + i, " ");
	if (!(is_valid_path(line, map->sprite_pass, i)))
		cub_file_err();
	(*obj_num)++;
}
