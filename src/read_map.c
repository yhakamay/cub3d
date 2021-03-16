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

static int	skip_spaces(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] == ' ')
		j++;
	return (j);
}

static void	check_obj(t_map *map, char *line, int *obj_num)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i += skip_spaces(line, i);
	//if (line[i] == '\0')
	//{
	//error
	//}
	if (line[i] == 'R')
	{
		i++;
		i += skip_spaces(line, i);
		//if(not number)
		//{
		//error
		//}
		while (line[i] >= '0' && line[i] <= '9')
		{
			//need error handring etc)into int
			map->window_width = map->window_width * 10 + line[i] - '0';
			i++;
		}
		i += skip_spaces(line, i);
		//if(not number or 改行)
		//{
		//error
		//}
		while (line[i] >= '0' && line[i] <= '9')
		{
			map->window_height = map->window_height * 10 + line[i] - '0';
			i++;
		}
		//if (いらないやつがこのあとにあったら)
		//{
		//error
		//}
		(*obj_num)++;
	}
	else if (line[i] == 'N' && line[i + 1] == 'O')
	{
		//if (line[i + 2] == '\0')
		//{
		//error
		//}
		i += 2;
		map->north_pass = ft_strtrim(line + i, " ");
		//if (いらないやつがこのあとにあったら)
		//{
		//error
		//}
		(*obj_num)++;
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		//if (line[i + 2] == '\0')
		//{
		//error
		//}
		i += 2;
		map->south_pass = ft_strtrim(line + i, " ");
		//if (いらないやつがこのあとにあったら)
		//{
		//error
		//}
		(*obj_num)++;
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		//if (line[i + 2] == '\0')
		//{
		//error
		//}
		i += 2;
		map->west_pass = ft_strtrim(line + i, " ");
		//if (いらないやつがこのあとにあったら)
		//{
		//error
		//}
		(*obj_num)++;
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		//if (line[i + 2] == '\0')
		//{
		//error
		//}
		i += 2;
		map->east_pass = ft_strtrim(line + i, " ");
		//if (いらないやつがこのあとにあったら)
		//{
		//error
		//}
		(*obj_num)++;
	}
	else if (line[i] == 'S')
	{
		//if (line[i + 1] == '\0')
		//{
		//error
		//}
		i++;
		map->sprite_pass = ft_strtrim(line + i, " ");
		//if (いらないやつがこのあとにあったら)
		//{
		//error
		//}
		(*obj_num)++;
	}
	else if (line[i] == 'F')
	{
		i++;
		i += skip_spaces(line, i);
		while (j < 3)
		{
			while (line[i] >= '0' && line[i] <= '9')
			{
				map->floor_rgb[j] = map->floor_rgb[j] * 10 + line[i] - '0';
				i++;
			}
			//if (map->floor_rgb[j] > 255 || そもそもおかしかったら)
			//{
			//error
			//}
			i++;
			j++;
		}
		(*obj_num)++;
	}
	else if (line[i] == 'C')
	{
		i++;
		i += skip_spaces(line, i);
		while (j < 3)
		{
			while (line[i] >= '0' && line[i] <= '9')
			{
				map->ceilling_rgb[j] = map->ceilling_rgb[j] * 10 + line[i] - '0';
				i++;
			}
			//if (map->ceilling_rgb[j] == -1 || map->ceillingrgb[j] > 255)
			//{
			//error
			//}
			i++;
			j++;
		}
		(*obj_num)++;
	}
}

static void offset_map(t_map *map)
{
	map->window_width = 0;
	map->window_height = 0;
	map->floor_rgb[0] = 0;
	map->floor_rgb[1] = 0;
	map->floor_rgb[2] = 0;
	map->ceilling_rgb[0] = 0;
	map->ceilling_rgb[1] = 0;
	map->ceilling_rgb[2] = 0;
	ft_memset(map->grid, 0, 200 * 201);
	ft_memset(map->reached, false, 200 * 200);
}

static void	make_map(t_map *map, char *line)
{
	static int	i;
	int			len;

	len = ft_strlen(line);
	;
	//if ((len > 200)
	//{
	//error;
	//}
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
	{
		no_file_err();
		exit(0);
	}
	obj_num = 0;
	offset_map(map);
	while (get_next_line(fd, &line))
	{
		if (obj_num < 8)
			check_obj(map, line, &obj_num);
		else
			make_map(map, line);
		free(line);
	}
	make_map(map, line);
	free(line);
}
