#ifndef CUB3D_H
#define CUB3D_H

#define DEBUG_ON 1

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

#include "../mlx/mlx.h"
#include "../gnl/get_next_line.h"
#include "../libft/libft.h"

#define WINDOW_TITLE "cub3d"

#define X_EVENT_KEY_PRESSED 2
#define X_EVENT_KEY_RELEASED 3

#define COLOR_BLACK 000000

#define MINIMAP_SCALE_FACTOR 1.0
#define TILE_SIZE 20

#define NUM_RAYS 100

#define PI 3.14159265
#define TWO_PI 6.28318530

#define PLAYER_WALK_SPEED 10
#define PLAYER_TURN_SPEED 10 * (PI / 180)
#define PLAYER_DIAMETER 2
#define PLAYER_COLOR 0x00FF0000

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

typedef struct s_rc_utils
{
	bool is_ray_facing_down;
	bool is_ray_facing_up;
	bool is_ray_facing_right;
	bool is_ray_facing_left;
	float x_intercept;
	float y_intercept;
	float x_step;
	float y_step;
	bool found_horz_wall_hit;
	float horz_wall_hit_x;
	float horz_wall_hit_y;
	float next_horz_touch_x;
	float next_horz_touch_y;
	bool found_vert_wall_hit;
	float vert_wall_hit_x;
	float vert_wall_hit_y;
	float next_vert_touch_x;
	float next_vert_touch_y;
	float horz_hit_distance;
	float vert_hit_distance;
} t_rc_utils;

typedef struct s_map
{
	int window_width;
	int window_height;
	char *north_pass;
	char *south_pass;
	char *west_pass;
	char *east_pass;
	char *sprite_pass;
	int floor_rgb[3];
	int ceilling_rgb[3];
	char grid[200][201];
} t_map;

typedef struct s_params
{
	t_mlx mlx;
	t_img img;
	t_player player;
	t_ray ray;
	t_map map;
	t_rc_utils rc_utils;
} t_params;

void my_mlx_pixel_put(t_img *img, int x, int y, int color);
void exit_game(t_mlx *mlx_ptr, t_mlx *win_ptr);
void init_player(t_player *player, t_map *map);
float normalize_angle(float rotation_angle);
void refresh_img(t_img *img, t_map *map);
void render_everything(t_params *params);
void move_player(t_player *player, t_img *img, t_map *map);
t_ray cast_ray(t_params *params, t_player *player, float ray_angle);
bool has_wall_at(int x, int y, t_map *map);
int key_pressed(int keycode, t_params *params);
int key_released(int keycode, t_params *params);
void read_map(char *file_pass, t_map *map);
int no_args_err(void);

#endif
