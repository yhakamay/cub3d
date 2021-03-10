#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

#include "../mlx/mlx.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "cub3d"

#define X_EVENT_KEY_PRESSED 2
#define X_EVENT_KEY_RELEASED 3

#define COLOR_BLACK 000000

#define MINIMAP_SCALE_FACTOR 1.0
#define TILE_SIZE 20

#define NUM_RAYS 10

#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

#define PI 3.14159265
#define TWO_PI 6.28318530

#define PLAYER_WALK_SPEED 10
#define PLAYER_TURN_SPEED 10 * (PI / 180)
#define PLAYER_DIAMETER 8
#define PLAYER_COLOR 0x00FF0000
#define PLAYER_RAY_LENGTH 50
#define PLAYER_RAY_RESOLUTION 2
#define PLAYER_LINE 20

#define FOV_ANGLE (60 * (PI / 180))

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
	int color;
	int x;
	int y;
	int width;
	int height;
	float turn_direction; // -1 for left, +1 for right;
	float walk_direction;
	float rotation_angle;
	float walk_speed;
	float turn_speed;
} t_player;

typedef struct s_ray
{
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	bool was_hit_vertical;
	bool is_ray_facing_up;
	bool is_ray_facing_down;
	bool is_ray_facing_left;
	bool is_ray_facing_right;
	bool wall_hit_content;
} t_ray;

// t_params holds all of parameters
typedef struct s_params
{
	t_mlx mlx;
	t_img img;
	t_player player;
	t_ray ray;
} t_params;

void my_mlx_pixel_put(t_img *img, int x, int y, int color);
void exit_game(t_mlx *mlx_ptr, t_mlx *win_ptr);
void init_player(t_player *player);
float normalize_angle(float rotation_angle);
void refresh_img(t_img *img);
// void render_line(int x_start, int y_start, float rotaion_angle, int length, int color, t_img *img);
void render_line(t_img *img, int x1, int y1, int x2, int y2, int color);
void render_rect(int x, int y, int width, int height, int color, t_img *img);
void render_circle(int x, int y, int r, int color, t_img *img);
void render_everything(t_params *params);
void move_player(t_player *player, t_img *img);
t_ray cast_ray(t_params *params, t_player *player, float ray_angle);
void render_rays(t_params *params, t_player *player, t_img *img);
bool has_wall_at(int x, int y);
int key_pressed(int keycode, t_params *params);
int key_released(int keycode, t_params *params);

float get_distance(float x1, float y1, float x2, float y2);
void render_player(t_player *player, t_img *img);
bool map_has_wall_at(float x, float y);

#endif
