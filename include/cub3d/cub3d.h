/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:24:34 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/15 10:13:28 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DEBUG_ON 0

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <float.h>

# include "../mlx/mlx.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"

# define WINDOW_TITLE "cub3d"

# define KEY_PRESSED 2
# define KEY_RELEASED 3
# define WINDOW_CLOSED 17

# define COLOR_BLACK 0x000000
# define COLOR_GRAY 0x808080
# define COLOR_DARK_GRAY 0x303030
# define COLOR_LIGHT_GRAY 0x858585
# define COLOR_WHITE 0xFFFFFF
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_CYAN 0x00FFFF
# define COLOR_MAGENTA 0xFF00FF

# define MINIMAP_SCALE_FACTOR 1.0
# define TILE_SIZE 20

# define PI 3.14159265
# define TWO_PI 6.28318530

# define PLAYER_WALK_SPEED 2
# define PLAYER_TURN_SPEED 3 * (PI / 180)
# define PLAYER_DIAMETER 2
# define PLAYER_COLOR COLOR_RED

# define FOV_ANGLE (60 * (PI / 180))

# define FILE_H_SIZE 14
# define INFO_H_SIZE 40

/*
** these are based on macOS
** if you want to use on other OS, replace them
** see: https://qiita.com/baba163/items/e2390c4529ec0448151d
*/
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_ARROW_RIGHT 123
# define KEY_ARROW_LEFT 124

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_texture
{
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
	t_img	sprite;
}				t_texture;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef struct	s_player
{
	int		color;
	int		x;
	int		y;
	int		width;
	int		height;
	float	turn_direction;
	float	walk_direction_vert;
	float	walk_direction_horz;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}				t_player;

typedef struct	s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	float	length_from_leftside;
	bool	was_hit_vertical;
	bool	is_facing_up;
	bool	is_facing_down;
	bool	is_facing_left;
	bool	is_facing_right;
	bool	wall_hit_content;
}				t_ray;

typedef struct	s_rc_utils
{
	bool	is_facing_down;
	bool	is_facing_up;
	bool	is_facing_right;
	bool	is_facing_left;
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	bool	found_horz_wall_hit;
	float	horz_wall_hit_x;
	float	horz_wall_hit_y;
	float	next_horz_touch_x;
	float	next_horz_touch_y;
	bool	found_vert_wall_hit;
	float	vert_wall_hit_x;
	float	vert_wall_hit_y;
	float	next_vert_touch_x;
	float	next_vert_touch_y;
	float	horz_hit_distance;
	float	vert_hit_distance;
}				t_rc_utils;

typedef struct	s_map
{
	int		window_width;
	int		window_height;
	char	*north_pass;
	char	*south_pass;
	char	*west_pass;
	char	*east_pass;
	char	*sprite_pass;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	char	grid[200][201];
	bool	reached[200][200];
}				t_map;

typedef struct	s_sprite
{
	int		x;
	int		y;
	float	distance;
	float	angle;
	bool	visible;
}				t_sprite;

typedef struct	s_params
{
	t_mlx		mlx;
	t_img		img;
	t_texture	texture;
	t_player	player;
	t_ray		*rays;
	t_map		map;
	t_rc_utils	rc_utils;
	t_sprite	*sprites;
}				t_params;

extern int	g_num_rays;
extern int	g_wall_strip_width;
extern int	g_num_sprites;

void			init_g_val(t_params *params);
void			init_player(t_player *player);
void			init_rc_utils_horz(
					t_rc_utils *rc_utils, t_player *player, float ray_angle);
void			init_rc_utils_vert(
					t_rc_utils *rc_utils, t_player *player, float ray_angle);
bool			is_player(t_params *params, char c);
bool			is_sprite(char c);
bool			is_forbidden_char(char c);
int				is_map_closed(t_map *map, int x, int y);
int				key_pressed(int keycode, t_params *params);
int				key_released(int keycode, t_params *params);
float			get_distance(float x1, float y1, float x2, float y2);
void			calculate_ray_angle(t_rc_utils *rc_utils, float ray_angle);
bool			is_around_window(t_rc_utils *rc_utils, t_map *map);
void			move_player(t_player *p, t_map *map);
int				exit_game(void);
float			normalize_angle(float rotation_angle);
bool			has_wall_at(float x, float y, t_map *map);
bool			has_sprite_at(float x, float y, t_map *map);
void			render_everything(t_params *params);
t_ray			cast_ray(t_params *params, t_player *player, float ray_angle);
void			read_map(char *file_path, t_map *map);
void			check_map(t_params *params);
void			screenshot_err(void);
void			no_args_err(void);
void			no_file_err(void);
void			cub_file_err(void);
int				num_of_spaces(char *line, int i);
int				num_of_numbers(char *line, int i);
void			get_resolution(t_map *map, char *line, int i, int *obj_num);
void			get_wall_texture(t_map *map, char *line, int i, int *obj_num);
void			get_floor_texture(t_map *map, char *line, int i, int j);
void			get_ceiling_texture(t_map *map, char *line, int i, int j);
void			get_sprite_texture(t_map *map, char *line, int i, int *obj_num);
void			get_north_path(char *line, int i, t_map *map);
void			get_south_path(char *line, int i, t_map *map);
void			get_west_path(char *line, int i, t_map *map);
void			get_east_path(char *line, int i, t_map *map);
bool			is_valid_path(char *line, char *path, int i);
void			save_screenshot(t_params *params);
void			draw_pixel(t_img *img, int x, int y, int color);
void			render_ceiling(t_img *img, t_map *map);
void			render_floor(t_img *img, t_map *map);
void			render_sprites(t_params *params);
bool			is_inside_fov(t_map *map, int height, int i);
void			normalize_p_sprite_angle(float *p_sprite_angle, t_player *p);
int				calculate_left_end_x(t_params *params, float distance_to_plane,
					int i, int wall_strip_height);
char			*calculate_color_addr(t_texture *texture, int height,
					int i, int j);

#endif
