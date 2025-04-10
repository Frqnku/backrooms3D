/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:13 by khadj-me          #+#    #+#             */
/*   Updated: 2025/04/10 15:02:31 by khadj-me         ###   ########.fr       */
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
		while (++j < ft_strlen(g_data.map.map[i]))
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

u_int32_t    *get_pixel(t_texture *img, int ray_x, int ray_y)
{
    return ((u_int32_t *)img->data + ray_y * (img->size_line / 4) + ray_x);
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
	int 	col;
	
	cos_value = cos(start_x);
	sin_value = sin(start_x);
	ray_x = g_data.player.coor[X];
	ray_y = g_data.player.coor[Y];
	col = 0;
	while (!wall_col(ray_x, ray_y, start_x))
	{	
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0x0000FF);
		ray_x += cos_value;
		ray_y += sin_value;
	}
	norm = find_norm(g_data.player.coor[X], ray_x, g_data.player.coor[Y], ray_y);
	height = TILE_SIZE / norm * (WIN_WIDTH / 1.5);
	start_y =  (WIN_HEIGHT - height) / 2;
	end = start_y + height;
	while (col < start_y)
		put_pixel(i, col++, g_data.colors[0].color);
	col = wall_col(ray_x, ray_y, start_x);
	while (start_y < end)
	{
		if (!DEBUG)
		{
			if (col == NORTH || col == SOUTH)
				put_pixel(i, start_y, *get_pixel(&g_data.textures[col - 1], fmodf(ray_x * (TILE_SIZE / TILE_SIZE), TILE_SIZE), (start_y - (WIN_HEIGHT / 2.0) + (height / 2)) * TILE_SIZE / height));
			else
				put_pixel(i, start_y, *get_pixel(&g_data.textures[col - 1], fmodf(ray_y * (TILE_SIZE / TILE_SIZE), TILE_SIZE), (start_y - (WIN_HEIGHT / 2.0) + (height / 2)) * TILE_SIZE / height));
		}
		start_y++;
	}
	while (end < WIN_HEIGHT)
		put_pixel(i, end++, g_data.colors[1].color);
	
}
