#include "../include/cub3d/cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void init_player(t_player *player)
{
	player->x = WINDOW_WIDTH / 2;
	player->y = WINDOW_HEIGHT / 2;
	player->color = PLAYER_COLOR;
	player->width = PLAYER_DIAMETER;
	player->height = PLAYER_DIAMETER;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = 0;
	player->walk_speed = PLAYER_WALK_SPEED;
	player->turn_speed = PLAYER_TURN_SPEED;
}

void refresh_img(t_img *img)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(img, i, j, COLOR_BLACK);
			j++;
		}
		i++;
	}
}

void render_line(int x_start, int y_start, float rotaion_angle, int length, int color, t_img *img)
{
	int x_end;
	int y_end;
	int x_sign;
	int x_delta;
	int x_base_len;
	int i;

	x_end = x_start + cos(rotaion_angle) * length;
	y_end = y_start + sin(rotaion_angle) * length;

	x_delta = x_end - x_start;
	x_sign = x_delta < 0 ? -1 : 1;
	x_base_len = abs(x_delta);

	i = 0;
	while (i < x_base_len)
	{
		my_mlx_pixel_put(img, x_start + (i * x_sign), y_start + (tan(rotaion_angle) * i * x_sign), color);
		i++;
	}
}

void render_circle(int x, int y, int r, int color, t_img *img)
{
	int x_i;
	int y_i;

	x_i = x - r;
	while (x_i < x + r)
	{
		y_i = y - r;
		while (y_i < y + r)
		{
			if ((pow((y_i - x), 2.0)) + pow((x_i - y), 2.0) <= pow(r, 2.0))
				my_mlx_pixel_put(img, x_i, y_i, color);
			y_i++;
		}
		x_i++;
	}
}

void render_rect(int x, int y, int width, int height, int color, t_img *img)
{
	int x_i;
	int y_i;

	x_i = x - (width / 2);
	while (x_i < x + width / 2)
	{
		y_i = y - (height / 2);
		while (y_i < y + height / 2)
		{
			my_mlx_pixel_put(img, x_i, y_i, color);
			y_i++;
		}
		x_i++;
	}
}

int key_pressed(int keycode, t_params *params)
{
	if (keycode == KEY_ESC)
		exit_game(params->mlx.mlx_ptr, params->mlx.win_ptr);

	if (keycode == KEY_W)
		params->player.walk_direction = 1; // move forward
	else if (keycode == KEY_S)
		params->player.walk_direction = -1; // move backward
	// if (keycode == KEY_D)
	// if (keycode == KEY_A)
	else if (keycode == KEY_ARROW_LEFT)
		params->player.turn_direction = 1;
	else if (keycode == KEY_ARROW_RIGHT)
		params->player.turn_direction = -1;
	else
		return (1);

	move_player(&params->player, &params->img);
	render_everything(params);

	return (1);
}

int key_released(int keycode, t_params *params)
{
	if (keycode == KEY_W)
		params->player.walk_direction = 0;
	else if (keycode == KEY_S)
		params->player.walk_direction = 0;
	// if (keycode == KEY_D)
	// if (keycode == KEY_A)
	else if (keycode == KEY_ARROW_LEFT)
		params->player.turn_direction = 0;
	else if (keycode == KEY_ARROW_RIGHT)
		params->player.turn_direction = 0;
	else
		return (1);

	move_player(&params->player, &params->img);
	render_everything(params);

	return (1);
}
