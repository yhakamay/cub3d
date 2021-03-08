#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "../include/mlx/mlx.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "cub3d"

#define MINIMAP_SCALE_FACTOR 1.0
#define TILE_SIZE 20

#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

#define PI 3.14159265
#define TWO_PI 6.28318530

#define PLAYER_WALK_SPEED 10
#define PLAYER_TURN_SPEED 10 * (PI / 180)
#define PLAYER_DIAMETER 5
#define PLAYER_COLOR 0x00FF0000
#define PLAYER_LINE 20

// these are based on macOS
// if you want to use on other OS, replace them
// see: https://qiita.com/baba163/items/e2390c4529ec0448151d
#define KEY_ESC 53
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13
#define KEY_ARROW_RIGHT 123
#define KEY_ARROW_LEFT 124

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
} t_mlx;

typedef struct s_player
{
	int x;
	int y;
	int color;
	int width;
	int height;
	int turn_direction; // -1 for left, +1 for right;
	int walk_direction;
	float rotation_angle;
	float walk_speed;
	float turn_speed;
} t_player;

// t_params holds all of parameters
typedef struct s_params
{
	t_mlx mlx;
	t_img img;
	t_player player;
} t_params;

void my_mlx_pixel_put(t_img *img, int x, int y, int color);
void init_player(t_player *player);

#endif
