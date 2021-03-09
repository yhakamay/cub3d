/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuki <matsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:16:37 by matsuki           #+#    #+#             */
/*   Updated: 2021/03/09 11:13:35 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_map.h"

//int[200][200]	map;

int		skip_spaces(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] == ' ')
	{
		j++;
	}
	return (j);
}

void	check_obj(t_map *map, char *line, int *obj_num)
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

void	offset_map(t_map *map)
{
	map->window_width = 0;
	map->window_height = 0;
	map->floor_rgb[0] = 0;
	map->floor_rgb[1] = 0;
	map->floor_rgb[2] = 0;
	map->ceilling_rgb[0] = 0;
	map->ceilling_rgb[1] = 0;
	map->ceilling_rgb[2] = 0;
	ft_memset(map->map, 0, 200 * 201);
}

void	make_map(t_map *map, char* line)
{
	static int	i;
	int			len;

	len = ft_strlen(line);;
	//if ((len > 200)
	//{
		//error;
	//}
	ft_memcpy(map->map[i], line, len + 1);
	i++;
}

void	read_map(char* file_pass, t_map *map)
{
	char	*line;
	int		fd;
	int		obj_num;

	//if (file is not .cub file)
	//{
		//error
	//}
	fd = open(file_pass, O_RDONLY);
	if (fd == -1)
	{
		//error
		return ;
	}
	obj_num = 0;
	offset_map(map);
	while (get_next_line(fd, &line))
	{
		if (obj_num < 8)
		{
			check_obj(map, line, &obj_num);
			printf("%d\n", obj_num);
		}
		else
		{
			printf("a\n");
			make_map(map, line);
		}
		free(line);
	}
	make_map(map, line);
	free(line);
}

//動作確認用のmain
int		main(int argc, char **argv)
{
	t_map	map;
	int	i;

	(void)argc;
	i = 0;
	read_map(argv[1], &map);
	printf("window_width: %d\n", map.window_width);
	printf("window_height: %d\n", map.window_height);
	printf("north_pass: %s\n", map.north_pass);
	printf("south_pass: %s\n", map.south_pass);
	printf("west_pass: %s\n", map.west_pass);
	printf("east_pass: %s\n", map.east_pass);
	printf("sprite_pass: %s\n", map.sprite_pass);
	printf("floor r,g,b: %d,%d,%d\n", map.floor_rgb[0], map.floor_rgb[1], map.floor_rgb[2]);
	printf("ceilling r,g,b: %d,%d,%d\n", map.ceilling_rgb[0], map.ceilling_rgb[1], map.ceilling_rgb[2]);
	printf("map\n");
	while (map.map[i][0] != '\0')
	{
		printf("%s\n", map.map[i]);
		i++;
	}
	return (0);
}
