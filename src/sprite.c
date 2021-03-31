/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:21:46 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/26 21:21:47 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

// s_sprite *sprites[g_num_sprites] (hakamaya)
// s_sprite *visible_sprites[g_num_sprites] (atsuki)
// FOVに入ってるspriteを、visible_spritesにコピーする (atan2を使う) (atsuki)
// visible_spritesを遠い順にソートする
// visible_spritesを描画する

static void	check_visible_sprites(t_params *params)
{
	int			i;
	float		angle_sprite_player;

	//変数の初期化
	i = 0;
	//spriteがvisibleかどうか判定するループ
	while (i < g_num_sprites)
	{
		////////spriteとの距離を更新////////
		params->sprites[i].distance = get_distance(params->player.x, params->player.y, params->sprites[i].x, params->sprites[i].y);

		////////angle_sprite_playerの計算////////
		//playerの位置からのspriteの絶対角度の導出
		angle_sprite_player = atan2(-(params->sprites[i].y - params->player.y), params->sprites[i].x - params->player.x);
		//atan2の戻り値をcub3dの角度の取り方に直す
		if (angle_sprite_player < 0)
			angle_sprite_player *= -1;
		else
			angle_sprite_player = 2 * PI - angle_sprite_player;
		//playerからの相対角度に直す
		printf("%f\n", angle_sprite_player * 180 / PI);
		angle_sprite_player = angle_sprite_player - params->player.rotation_angle;
		printf("%f\n", angle_sprite_player * 180 / PI);
		//0~PIの範囲に直す
		if (angle_sprite_player > PI)
			angle_sprite_player -= 2 * PI;
		else if (angle_sprite_player < -PI)
			angle_sprite_player += 2 * PI;
		params->sprites[i].angle = angle_sprite_player;
		printf("%f\n", angle_sprite_player * 180 / PI);
		angle_sprite_player = fabs(angle_sprite_player);

		//visible判定
		//float	epsilon = 0.2;
		
		if (angle_sprite_player <= (float)(FOV_ANGLE / 2))
			params->sprites[i].visible = true;
		else
			params->sprites[i].visible = false;
		//printf("%d\n", params->sprites[i].visible);
		i++;
	}
}

static void	sort_sprites(t_params *params)
{
	int			i;
	int			j;
	t_sprite	temp;

	//変数の初期化
	i = 0;

	//bubble sort
	while (i < g_num_sprites - 1)
	{
		j = g_num_sprites - 1;
		while (j > i)
		{
			if (params->sprites[j - 1].distance < params->sprites[j].distance)
			{
				temp = params->sprites[j];
				params->sprites[j] = params->sprites[j - 1];
				params->sprites[j - 1] = temp;
			}
			j--;
		}
		i++;
	}
}

static void	render_one_sprite(t_params *params, t_img *img, int x, int height)
{
	char	*color_addr;
	int		color;
	float	col;
	int		i;
	int		j;

	col = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < height)
		{
			color_addr = img->addr + (int)roundf(i * img->height / height) * img->line_length + (int)roundf(j * img->width / height) * (img->bits_per_pixel / 8);
			color = *(int *)color_addr;
			if (params->map.window_height / 2 - height / 2 + i >= 0 && params->map.window_height / 2 - height / 2 + i < params->map.window_height && x + j >= 0 && x + j < params->map.window_width)
			{
				if (color != 0)
					draw_pixel(&params->img, x + j, params->map.window_height / 2 - height / 2 + i, *(int *)(color_addr));
			}
			j++;
		}
		i++;
	}
}

void	render_sprites(t_params *params)
{
	int		i = 0;
	int		left_end_x;
	int		wall_strip_height;
	float	correct_wall_distance;
	float	distance_to_plane;

	check_visible_sprites(params);
	sort_sprites(params);
	while (i < g_num_sprites)
	{
		if (!params->sprites[i].visible)
		{
			i++;
			continue ;
		}
		correct_wall_distance = params->sprites[i].distance * cos(params->sprites[i].angle);
		distance_to_plane = (params->map.window_width / 2) / tan(FOV_ANGLE / 2);
		wall_strip_height = (TILE_SIZE / correct_wall_distance) * distance_to_plane;
		left_end_x = params->map.window_width / 2 + distance_to_plane * tan(params->sprites[i].angle) - wall_strip_height / 2;
		render_one_sprite(params, &params->texture.sprite, left_end_x, wall_strip_height);
		i++;
	}
}