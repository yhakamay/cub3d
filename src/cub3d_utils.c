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
	player->rotation_angle = PI / 2;
	player->walk_speed = PLAYER_WALK_SPEED;
	player->turn_speed = PLAYER_TURN_SPEED;
}

void render_line(float x_start, float y_start, float rotaion_angle, float length, int color, t_img *img)
{
	float x_end;
	float y_end;

	x_end = x_start + (cos(rotaion_angle) * length);
	y_end = y_start + (sin(rotaion_angle) * length);

	my_mlx_pixel_put(img, x_end, y_end, color);
}

// TODO: x, y, width, and height should be float
void render_rect(int x, int y, int width, int height, int color, t_img *img)
{
	int i;
	int j;

	i = x;
	while (i < x + width)
	{
		j = y;
		while (j < y + height)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
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

	printf("player.walk_direction: %f\n", params->player.walk_direction);

	move_player(&params->player, &params->img);
	render_everything(params);

	// printf("▼▼▼▼▼\n");
	// printf("player.x: %f\n", params->player.x);
	// printf("player.y: %f\n", params->player.y);
	// printf("▲▲▲▲▲\n\n\n");

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
