/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:26 by utiberto          #+#    #+#             */
/*   Updated: 2025/04/11 15:32:57 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backrooms.h"
#include <stdio.h>

t_data		g_data;

static void	player_inputs(t_player *player, float cos_value, float sin_value)
{
	if (player->w == PRESSED && !wall_col(player->coor[X] + cos_value * SPEED,
			player->coor[Y] + sin_value * SPEED, 0))
	{
		player->coor[X] += cos_value * SPEED;
		player->coor[Y] += sin_value * SPEED;
	}
	if (player->s == PRESSED && !wall_col(player->coor[X] - cos_value * SPEED,
			player->coor[Y] - sin_value * SPEED, 0))
	{
		player->coor[X] -= cos_value * SPEED;
		player->coor[Y] -= sin_value * SPEED;
	}
	if (player->a == PRESSED && !wall_col(player->coor[X] + sin_value * SPEED,
			player->coor[Y] - cos_value * SPEED, 0))
	{
		player->coor[X] += sin_value * SPEED;
		player->coor[Y] -= cos_value * SPEED;
	}
	if (player->d == PRESSED && !wall_col(player->coor[X] - sin_value * SPEED,
			player->coor[Y] + cos_value * SPEED, 0))
	{
		player->coor[X] -= sin_value * SPEED;
		player->coor[Y] += cos_value * SPEED;
	}
}

void	move_player(t_player *player)
{
	float	cos_value;
	float	sin_value;

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
	player_inputs(player, cos_value, sin_value);
}

int	game_loop(t_data *data)
{
	int		i;
	float	div;
	float	start_x;

	i = 0;
	move_player(&data->player);
	clear_screen();
	div = PI / 3 / WIN_WIDTH;
	start_x = data->player.view - PI / 6;
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
	mlx_put_image_to_window(g_data.mlx, g_data.mlx_window, g_data.mlx_img, 0,
		0);
	return (0);
}

int	main(int ac, char **av)
{
	init_data(ac, av);
	mlx_hook(g_data.mlx_window, KeyPress, KeyPressMask, &on_keypress, &g_data);
	mlx_hook(g_data.mlx_window, KeyRelease, KeyReleaseMask, &on_keyrelease,
		&g_data);
	mlx_hook(g_data.mlx_window, DestroyNotify, StructureNotifyMask,
		&destroy_game, &g_data);
	mlx_loop_hook(g_data.mlx, &game_loop, &g_data);
	mlx_loop(g_data.mlx);
	return (0);
}
