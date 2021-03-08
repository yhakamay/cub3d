#include "cub3d.h"

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
