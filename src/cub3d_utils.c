#include "cub3d.h"

void my_mlx_pixel_put(t_params *params, int x, int y, int color)
{
	char *dst;

	dst = params->img.addr + (y * params->img.line_length + x * (params->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void init_player(t_params *params)
{
	params->player.x = WINDOW_WIDTH / 2;
	params->player.y = WINDOW_HEIGHT / 2;
	params->player.width = 20;
	params->player.height = 20;
	params->player.turn_direction = 0;
	params->player.walk_direction = 0;
	params->player.rotation_angle = PI / 2;
	params->player.walk_speed = 200;
	params->player.turn_speed = 90 * (PI / 180);
}
