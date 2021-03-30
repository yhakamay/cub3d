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

	printf("before while loop in check_visible_sprites()\n");
	//spriteがvisibleかどうか判定するループ
	printf("g_num_sprites: %d\n", g_num_sprites);
	while (i < g_num_sprites)
	{
		/////////////////////////////////
		//        SERIOUS ERROR        //
		/////////////////////////////////
		////////spriteとの距離を更新////////
		float distance;
		printf("before get_distance()\n");
		params->sprites[i].distance = get_distance(params->player.x, params->player.y, params->sprites[i].x, params->sprites[i].y);
		/////////////////////////////////
		//        SERIOUS ERROR        //
		/////////////////////////////////

		////////angle_sprite_playerの計算////////
		//playerの位置からのspriteの絶対角度の導出
		angle_sprite_player = atan2(params->sprites[i].y - params->player.y, params->sprites[i].x - params->player.x);
		//atan2の戻り値をcub3dの角度の取り方に直す
		if (angle_sprite_player < 0)
			angle_sprite_player *= -1;
		else
			angle_sprite_player = 2 * PI - angle_sprite_player;
		//playerからの相対角度に直す
		angle_sprite_player = angle_sprite_player - params->player.rotation_angle;
		//0~PIの範囲に直す
		if (angle_sprite_player > PI)
			angle_sprite_player -= 2 * PI;
		else if (angle_sprite_player < -PI)
			angle_sprite_player += 2 * PI;
		angle_sprite_player = fabs(angle_sprite_player);

		//visible判定
		float	epsilon = 0.2;
		if (angle_sprite_player <= (float)(FOV_ANGLE / 2) + epsilon)
			params->sprites[i].visible = true;
		else
			params->sprites[i].visible = false;
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

void	render_sprites(t_params *params)
{
	int	i = 0;

	printf("before check_visible_sprites()\n");
	check_visible_sprites(params);
	printf("after check_visible_sprites()\n");
	sort_sprites(params);
	while(i < g_num_sprites)
	{
		printf("distance : %f\n", params->sprites[i].distance);
		printf("visible : %d\n", params->sprites[i].visible);
		printf("\n");
		i++;
	}
}
