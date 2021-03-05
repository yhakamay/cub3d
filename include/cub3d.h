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

# define FPS 30
# define FRAME_TIME_LENGTH (1000 / FPS)

// these are based on macOS
// if you want to use on othe OS, replace them
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13

typedef struct	s_params
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_params;

typedef struct	s_player
{
	int		player_x;
	int		player_y;
}				t_player;

#endif
