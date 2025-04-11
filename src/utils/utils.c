/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:42:01 by khadj-me          #+#    #+#             */
/*   Updated: 2025/04/11 11:53:57 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

int	tblotbl_len(char **tbl)
{
	int	i;

	if (!tbl)
		return (0);
	i = 0;
	while (tbl[i] != NULL)
		i++;
	return (i);
}

int	is_in_charset(char c, const char *charset)
{
	if (!charset || !c)
		return (0);
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}

int	wall_col(float obj_x, float obj_y, float start_x)
{
	int	scaled_x;
	int	scaled_y;

	scaled_x = obj_x / TILE_SIZE;
	scaled_y = obj_y / TILE_SIZE;
	if (g_data.map.map[scaled_y][scaled_x] == '1')
	{
		if (is_in_charset(g_data.map.map[(int)(obj_y - sin(start_x))
				/ TILE_SIZE][scaled_x], "0NSEW") == 1)
		{
			if (sin(start_x) < 0)
				return (SOUTH);
			return (NORTH);
		}
		else if (is_in_charset(g_data.map.map[scaled_y][(int)(obj_x
				- cos(start_x)) / TILE_SIZE], "0NSEW") == 1)
		{
			if (cos(start_x) < 0)
				return (EAST);
			return (WEST);
		}
		return (1);
	}
	return (0);
}

void	put_pixel(int x, int y, int color)
{
	char	*dst;

	dst = NULL;
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	dst = g_data.screen + (y * g_data.line_length + x * (g_data.bits_pr_pxl
				/ 8));
	*(unsigned int *)dst = color;
}

float	find_norm(float x1, float x2, float y1, float y2)
{
	float	delta_x;
	float	delta_y;
	float	view;
	float	fixed_norm;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	view = atan2(delta_y, delta_x) - g_data.player.view;
	fixed_norm = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(view);
	return (fixed_norm);
}
