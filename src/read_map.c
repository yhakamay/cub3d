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

static int	num_of_spaces(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] == ' ')
		j++;
	return (j);
}

static int	num_of_numbers(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] >= '0' && line[i + j] <= '9')
		j++;
	return (j);
}

static void get_direction(t_map *map, char *line, int i, int *obj_num)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		i += 2;
		if (line[i] != ' ')
			cub_file_err();
		map->north_pass = ft_strtrim(line + i, " ");
		if (ft_strlen(line + i) != ft_strlen(map->north_pass) + num_of_spaces(line, i))
			cub_file_err();
		(*obj_num)++;
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		i += 2;
		if (line[i] != ' ')
			cub_file_err();
		map->south_pass = ft_strtrim(line + i, " ");
		if (ft_strlen(line + i) != ft_strlen(map->south_pass) + num_of_spaces(line, i))
			cub_file_err();
		(*obj_num)++;
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		i += 2;
		if (line[i] != ' ')
			cub_file_err();
		map->west_pass = ft_strtrim(line + i, " ");
		if (ft_strlen(line + i) != ft_strlen(map->west_pass) + num_of_spaces(line, i))
			cub_file_err();
		(*obj_num)++;
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		i += 2;
		if (line[i] != ' ')
			cub_file_err();
		map->east_pass = ft_strtrim(line + i, " ");
		if (ft_strlen(line + i) != ft_strlen(map->east_pass) + num_of_spaces(line, i))
			cub_file_err();
		(*obj_num)++;
	}
}

static void get_wall_ceiling_color(t_map *map, char *line, int i, int j, int *obj_num, char f_or_c)
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

static void	check_obj(t_map *map, char *line, int *obj_num)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i += num_of_spaces(line, i);
	if (line[i] == 'R')
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
	else if ((line[i] == 'N' && line[i + 1] == 'O') ||
				(line[i] == 'S' && line[i + 1] == 'O') ||
				(line[i] == 'W' && line[i + 1] == 'E') ||
				(line[i] == 'E' && line[i + 1] == 'A'))
		get_direction(map, line, i, obj_num);
	else if (line[i] == 'S')
	{
		i++;
		if (line[i] != ' ')
			cub_file_err();
		map->sprite_pass = ft_strtrim(line + i, " ");
		if (ft_strlen(line + i) != ft_strlen(map->sprite_pass) + num_of_spaces(line, i))
			cub_file_err();
		(*obj_num)++;
	}
	else if (line[i] == 'F' || line[i] == 'C')
	{
		get_wall_ceiling_color(map, line, i, j, obj_num, line[i]);
	}
}

static void offset_map(t_map *map)
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
