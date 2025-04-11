/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:13 by khadj-me          #+#    #+#             */
/*   Updated: 2025/04/11 15:47:36 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backrooms.h"

void	draw_square(int x, int y, int color, int size)
{
	int	i;
	int	j;

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

void	draw_map(void)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = -1;
	len = tblotbl_len(g_data.map.map);
	while (++i < len)
	{
		while (++j < (int)ft_strlen(g_data.map.map[i]))
			if (g_data.map.map[i][j] == '1')
				draw_square(j * TILE_SIZE, i * TILE_SIZE, 0x00FF00, TILE_SIZE);
		j = -1;
	}
}

void	clear_screen(void)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < WIN_HEIGHT)
	{
		while (++j < WIN_WIDTH)
			put_pixel(j, i, 0x000000);
		j = -1;
	}
}

u_int32_t	*get_pixel(t_texture *img, int ray_x, int ray_y)
{
	return ((u_int32_t *)img->data + ray_y * (img->size_line / 4) + ray_x);
}

void	draw_fov(double start_x, int i)
{
	t_fov	fov;
	double	start_y;

	fov.ray_x = g_data.player.coor[X];
	fov.ray_y = g_data.player.coor[Y];
	col_loop(start_x, &fov.ray_x, &fov.ray_y);
	fov.height = TILE_SIZE / find_norm(g_data.player.coor[X], fov.ray_x,
			g_data.player.coor[Y], fov.ray_y) * (WIN_WIDTH / 1.5);
	start_y = (WIN_HEIGHT - fov.height) / 2;
	fov.end = start_y + fov.height;
	if (!DEBUG)
		draw_loop(start_x, start_y, i, &fov);
}
