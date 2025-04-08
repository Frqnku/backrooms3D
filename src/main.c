/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:26 by utiberto          #+#    #+#             */
/*   Updated: 2025/04/08 16:55:49 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backrooms.h"
#include <stdio.h>

t_data	g_data;
int 	spr_size = 32;

void find_spawn_coor()
{
	char **map = g_data.map.map;
	int i;
	int j;
	int len;

	i = -1;
	j = -1;
	len = tblotbl_len(map);
	while (++i < len)
	{
		while (++j < ft_strlen(map[i]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'O' || map[i][j] == 'E')
			{
				g_data.player.coor[X] = j * TILE_SIZE;		
				g_data.player.coor[Y] = i * TILE_SIZE;
				break ;
			}
			j++;
		}
		j = -1;
	}
}

int wall_col(float obj_x, float obj_y, float start_x)
{
	int scaled_x;
	int scaled_y;

	scaled_x = obj_x / TILE_SIZE;
	scaled_y = obj_y / TILE_SIZE;
	if (g_data.map.map[scaled_y][scaled_x] == '1')
	{	
		if (g_data.map.map[(int)(obj_y - sin(start_x)) / TILE_SIZE][scaled_x] == '0')
			return (VER_TOUCH);
		else if (g_data.map.map[scaled_y][(int)(obj_x - cos(start_x)) / TILE_SIZE] == '0')
			return (HOR_TOUCH);
		return (1);
	}
	return (0);
}

void put_pixel(int x, int y, int color)
{
	char *dst;
		
	dst = NULL;
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	dst = g_data.screen + (y * g_data.line_length + x * (g_data.bits_pr_pxl / 8));
	*(unsigned int *)dst = color;
}

float find_norm(float x1, float x2, float y1, float y2)
{
	float delta_x;
	float delta_y;
	float view;
	float fixed_norm;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	view = atan2(delta_y, delta_x) - g_data.player.view;
	fixed_norm = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(view);
	return (fixed_norm);
}

void move_player(t_player *player)
{
	float cos_value;
	float sin_value;

	cos_value = cos(player->view);
	sin_value = sin(player->view);
	if (player->l_arr == PRESSED)
		player->view -= ROTATE_SPEED;
	if (player->r_arr == PRESSED)
		player->view += ROTATE_SPEED;
	if (player->view > 2 * PI)
		player->view = 0;
	if (player->view < 0)
		player->view = 2 * PI;
	if (player->w == PRESSED && !wall_col(player->coor[X] + cos_value * SPEED, player->coor[Y] + sin_value * SPEED, 0))
	{
		player->coor[X] += cos_value * SPEED;
		player->coor[Y] += sin_value * SPEED;
	}
	if (player->s == PRESSED && !wall_col(player->coor[X] - cos_value * SPEED, player->coor[Y] - sin_value * SPEED, 0))
	{
		player->coor[X] -= cos_value * SPEED;
		player->coor[Y] -= sin_value * SPEED;
	}
	if (player->a == PRESSED && !wall_col(player->coor[X] + sin_value * SPEED, player->coor[Y] - cos_value * SPEED, 0))
	{
		player->coor[X] += sin_value * SPEED;
		player->coor[Y] -= cos_value * SPEED;
	}
	if (player->d == PRESSED && !wall_col(player->coor[X] - sin_value * SPEED, player->coor[Y] + cos_value * SPEED, 0))
	{
		player->coor[X] -= sin_value * SPEED;
		player->coor[Y] += cos_value * SPEED;
	}
}

int	game_loop(t_data *data)
{
	int i = 0;
	move_player(&data->player);
	clear_screen();
	float div = PI / 3 / WIN_WIDTH;
	float start_x = data->player.view - PI / 6;
	if (DEBUG)
	{
		draw_square(data->player.coor[X], data->player.coor[Y], 0xFF0000, 15);
		draw_map();
	}
	while (i < WIN_WIDTH)
	{
		draw_fov(start_x, i);
		start_x += div;
		i++;
	}
	mlx_put_image_to_window(g_data.mlx, g_data.mlx_window, g_data.mlx_img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	init_data(ac, av);

	mlx_hook(g_data.mlx_window, KeyPress, KeyPressMask, &on_keypress, &g_data);
	mlx_hook(g_data.mlx_window, KeyRelease, KeyReleaseMask, &on_keyrelease, &g_data);
	mlx_hook(g_data.mlx_window, DestroyNotify, StructureNotifyMask, &destroy_game,
		&g_data);
	mlx_loop_hook(g_data.mlx, &game_loop, &g_data);
	mlx_loop(g_data.mlx);
	
	return (0);
}
