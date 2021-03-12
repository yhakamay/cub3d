/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuki <matsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:19:22 by matsuki           #+#    #+#             */
/*   Updated: 2021/03/09 23:32:46 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../gnl/get_next_line.h"
#include "../libft/libft.h"

typedef struct	s_map
{
	int		window_width;
	int		window_height;
	char*	north_pass;
	char*	south_pass;
	char*	west_pass;
	char*	east_pass;
	char*	sprite_pass;
	int		floor_rgb[3];
	int		ceilling_rgb[3];
	char	map[200][201];
}				t_map;