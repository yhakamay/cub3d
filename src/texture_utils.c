/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 11:01:59 by yhakamay          #+#    #+#             */
/*   Updated: 2021/04/03 11:02:00 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

bool	is_valid_path(char *line, char *path, int i)
{
	if (ft_strlen(line + i) != ft_strlen(path) + num_of_spaces(line, i))
		return (false);
	return (true);
}

void	get_north_path(char *line, int i, t_map *map)
{
	i += 2;
	if (line[i] != ' ')
		cub_file_err();
	map->north_pass = ft_strtrim(line + i, " ");
	if (!(is_valid_path(line, map->north_pass, i)))
		cub_file_err();
}

void	get_south_path(char *line, int i, t_map *map)
{
	i += 2;
	if (line[i] != ' ')
		cub_file_err();
	map->south_pass = ft_strtrim(line + i, " ");
	if (!(is_valid_path(line, map->south_pass, i)))
		cub_file_err();
}

void	get_west_path(char *line, int i, t_map *map)
{
	i += 2;
	if (line[i] != ' ')
		cub_file_err();
	map->west_pass = ft_strtrim(line + i, " ");
	if (!(is_valid_path(line, map->west_pass, i)))
		cub_file_err();
}

void	get_east_path(char *line, int i, t_map *map)
{
	i += 2;
	if (line[i] != ' ')
		cub_file_err();
	map->east_pass = ft_strtrim(line + i, " ");
	if (!(is_valid_path(line, map->east_pass, i)))
		cub_file_err();
}
