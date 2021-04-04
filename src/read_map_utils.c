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

int			num_of_spaces(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] == ' ')
		j++;
	return (j);
}

int			num_of_numbers(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] >= '0' && line[i + j] <= '9')
		j++;
	return (j);
}

void		get_resolution(t_map *map, char *line, int i, int *obj_num)
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
	if (map->window_width > 1920)
		map->window_width = 1920;
	if (map->window_height > 1080)
		map->window_height = 1080;
	if (ft_strlen(line + i) != (size_t)num_of_spaces(line, i))
		cub_file_err();
	(*obj_num)++;
}
