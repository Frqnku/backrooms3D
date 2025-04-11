/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov_loops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:54:39 by khadj-me          #+#    #+#             */
/*   Updated: 2025/04/11 15:35:44 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backrooms.h"

void	col_loop(double start_x, double *ray_x, double *ray_y)
{
	double	cos_value;
	double	sin_value;

	cos_value = cos(start_x);
	sin_value = sin(start_x);
	while (!wall_col(*ray_x, *ray_y, start_x))
	{
		if (DEBUG)
			put_pixel(*ray_x, *ray_y, 0x0000FF);
		*ray_x += cos_value;
		*ray_y += sin_value;
	}
}

void	draw_loop(double start_x, double start_y, int i, t_fov *fov)
{
	int	col;

	col = 0;
	while (col < start_y)
		put_pixel(i, col++, g_data.colors[0].color);
	col = wall_col(fov->ray_x, fov->ray_y, start_x);
	while (start_y < fov->end)
	{
		if (col == NORTH || col == SOUTH)
			put_pixel(i, start_y, *get_pixel(&g_data.textures[col - 1],
					fmodf(fov->ray_x * (TILE_SIZE / TILE_SIZE), TILE_SIZE),
					(start_y - (WIN_HEIGHT / 2.0) + (fov->height / 2))
					* TILE_SIZE / fov->height));
		else
			put_pixel(i, start_y, *get_pixel(&g_data.textures[col - 1],
					fmodf(fov->ray_y * (TILE_SIZE / TILE_SIZE), TILE_SIZE),
					(start_y - (WIN_HEIGHT / 2.0) + (fov->height / 2))
					* TILE_SIZE / fov->height));
		start_y++;
	}
	while (fov->end < WIN_HEIGHT)
		put_pixel(i, fov->end++, g_data.colors[1].color);
}
