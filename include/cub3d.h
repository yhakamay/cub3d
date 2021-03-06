#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "../include/mlx/mlx.h"

# define FALSE 0
# define TRUE 1

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define WINDOW_TITLE "cub3d"

# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

# define FPS 30
# define FRAME_TIME_LENGTH (1000 / FPS)

#define MINIMAP_SCALE_FACTOR 1.0

#define PI 3.14159265
#define TWO_PI 6.28318530

// these are based on macOS
// if you want to use on othe OS, replace them
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13

# define COLOR_R 0x00FF0000

// s_data is a copy from 42 Docs
// if you want more info, see:
// https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#writing-pixels-to-a-image
typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_params
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			player_x;
	int			player_y;
	int			player_width;
	int			player_height;
	int			player_turn_direction; // -1 for left, +1 for right;
	int			player_walk_direction;
	float		player_rotation_angle;
	float		player_walk_speed;
	float		player_turn_speed;
}				t_params;

// typedef struct	s_player
// {
// 	int		x;
// 	int		y;
// 	int		width;
// 	int		height;
// 	int			turn_direction; // -1 for left, +1 for right;
// 	int			walk_direction;
// 	float		rotation_angle;
// 	float		walk_speed;
// 	float		turn_speed;
// }				t_player;

#endif
