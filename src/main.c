/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:26 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/29 17:46:33 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backrooms.h"
#include <stdio.h>

t_data	g_data;

int	destroy_game(t_data *data)
{
	cleanup();
	if (data->mlx)
	{
		if (data->mlx_img)
			mlx_destroy_image(data->mlx, data->mlx_img);
		if (data->mlx_window)
			mlx_destroy_window(data->mlx, data->mlx_window);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	}
	exit(1);
	return (0);
}

int on_keypress(int input, t_data *data)
{
	if (input == KEY_ESC)	
		destroy_game(data);
	if (input == KEY_W)
		data->player.w = PRESSED;
	if (input == KEY_S)
		data->player.s = PRESSED;
	if (input == KEY_A)
		data->player.a = PRESSED;
	if (input == KEY_D)
		data->player.d = PRESSED;
	if (input == ARROW_LEFT)
		data->player.l_arr = PRESSED;
	if (input == ARROW_RIGHT)
		data->player.r_arr = PRESSED;
	return (0);
}

int on_keyrelease(int input, t_data *data)
{
	if (input == KEY_W)
		data->player.w = RELEASED;
	if (input == KEY_S)
		data->player.s = RELEASED;
	if (input == KEY_A)
		data->player.a = RELEASED;
	if (input == KEY_D)
		data->player.d = RELEASED;
	if (input == ARROW_LEFT)
		data->player.l_arr = RELEASED;
	if (input == ARROW_RIGHT)
		data->player.r_arr = RELEASED;
	return (0);
}

int wall_col(float obj_x, float obj_y)
{
	int scaled_x;
	int scaled_y;

	scaled_x = obj_x / TILE_SIZE;
	scaled_y = obj_y / TILE_SIZE;
	if (g_data.map.map[scaled_y][scaled_x] == '1')
		return (1);
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

void init_data(int ac, char **av)
{
	g_data.player.coor[X] = 300;
	g_data.player.coor[Y] = 300;
	g_data.player.w = RELEASED;
	g_data.player.s = RELEASED;
	g_data.player.a = RELEASED;
	g_data.player.d = RELEASED;
	g_data.player.l_arr = RELEASED;
	g_data.player.r_arr = RELEASED;
	g_data.player.view = PI;
	g_data.mlx = NULL;
	g_data.mlx_window = NULL;
	g_data.mlx_img = NULL;
	g_data.screen = NULL;
	g_data.bits_pr_pxl = 0;
	g_data.line_length = 0;
	g_data.endian = 0;
	check_args(ac, av);
	g_data.mlx = mlx_init();
	if (!g_data.mlx)
		destroy_game(&g_data);
	g_data.mlx_window = mlx_new_window(g_data.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Backrooms 3D");
	if (!g_data.mlx_window)
		destroy_game(&g_data);
	g_data.mlx_img = mlx_new_image(g_data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!g_data.mlx_img)
		destroy_game(&g_data);
	g_data.screen = mlx_get_data_addr(g_data.mlx_img, &g_data.bits_pr_pxl, &g_data.line_length, &g_data.endian);	
	mlx_put_image_to_window(g_data.mlx, g_data.mlx_window, g_data.mlx_img, 0, 0);
}

void draw_square(int x, int y, int color, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		put_pixel(x + i, y + j, color);
		i++;
	}
	while (j < size)
	{
		put_pixel(x, y + j, color);
		put_pixel(x + i - 1, y + j, color);
		j++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + j - 1, color);
		i++;
	}
}

void draw_map()
{
	int i;
	int j;
	int len;

	i = -1;
	j = -1;
	len = tblotbl_len(g_data.map.map);
	while (++i < len)
	{	
		while (++j < ft_strlen(g_data.map.map[i]))
			if (g_data.map.map[i][j] == '1')
				draw_square(j * TILE_SIZE, i * TILE_SIZE, 0x00FF00, TILE_SIZE);
		j = -1;
	}
}

void clear_screen()
{
	int i;
	int j;
	
	i = -1;
	j = -1;
	while (++i < WIN_HEIGHT)
	{
		while (++j < WIN_WIDTH)
			put_pixel(j, i, 0x000000);
		j = -1;
	}
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
	printf("%f\n", fixed_norm);
	return (fixed_norm);
}

void draw_fov(float start_x, int i)
{
	float cos_value;
	float sin_value;
	float ray_x;
	float ray_y;
	float norm;
	float height;
	float start_y;
	float end;
	
	cos_value = cos(start_x);
	sin_value = sin(start_x);
	ray_x = g_data.player.coor[X];
	ray_y = g_data.player.coor[Y];
	while (!wall_col(ray_x, ray_y))
	{	
		//put_pixel(ray_x, ray_y, 0x0000FF);
		ray_x += cos_value;
		ray_y += sin_value;
	}
	norm = find_norm(g_data.player.coor[X], ray_x, g_data.player.coor[Y], ray_y);
	height = TILE_SIZE / norm * (WIN_WIDTH / 2);
	start_y =  (WIN_HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		put_pixel(i, start_y, 0x0000FF);
		start_y++;
	}
	
}

void move_player(t_player *player)
{
	float cos_value;
	float sin_value;

	cos_value = cos(player->view);
	sin_value = sin(player->view);
	if (player->l_arr == PRESSED)
		player->view -= 0.01;
	if (player->r_arr == PRESSED)
		player->view += 0.01;
	else if (player->view > 2 * PI)
		player->view = 0;
	if (player->view < 0)
		player->view = 2 * PI;
	if (player->w == PRESSED) // && !wall_col(player->coor[X] + sin_value * SPEED, player->coor[Y] + cos_value * SPEED))
	{
		player->coor[X] += cos_value * SPEED;
		player->coor[Y] += sin_value * SPEED;
	}
	if (player->s == PRESSED) // && !wall_col(player->coor[X] - sin_value * SPEED, player->coor[Y] - cos_value * SPEED))
	{
		player->coor[X] -= cos_value * SPEED;
		player->coor[Y] -= sin_value * SPEED;
	}
	if (player->a == PRESSED) // && !wall_col(player->coor[X] + cos_value * SPEED, player->coor[Y] - sin_value * SPEED))
	{
		player->coor[X] += cos_value * SPEED;
		player->coor[Y] -= sin_value * SPEED;
	}
	if (player->d == PRESSED) // && !wall_col(player->coor[X] - cos_value * SPEED, player->coor[Y] + sin_value * SPEED))
	{
		player->coor[X] -= cos_value * SPEED;
		player->coor[Y] += sin_value * SPEED;
	}
}

int	game_loop(t_data *data)
{
	int i = 0;
	float div = PI / 3 / WIN_WIDTH;
	float start_x = data->player.view - PI / 6;
	clear_screen();
	move_player(&data->player);
	// draw_square(data->player.coor[X], data->player.coor[Y], 0xFF0000, 15);
	// draw_map();
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
