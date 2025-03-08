/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:54:42 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/08 14:14:04 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"
#include <stdio.h>

static void	find_wall(char **map, int y, int x, int offset)
{
	while (y >= 0 && y < g_data.map.size)
	{
		if ((int)ft_strlen(map[y]) <= x)
			y += offset;
		else if (map[y][x] == ' ')
			y += offset;
		else if (is_wall(map[y][x]))
			return ;
		else
			handle_map_error(BADWALLS);
	}
}

static void	check_top_bottom(char **map)
{
	int	x;

	x = -1;
	while (map[0][++x])
		if (!is_wall(map[0][x]) && map[0][x] != ' ')
			handle_map_error(BADWALLS);
	x = -1;
	while (map[0][++x])
		if (map[0][x] == ' ')
			find_wall(map, 0, x, +1);
	x = -1;
	while (map[g_data.map.size - 1][++x])
		if (!is_wall(map[g_data.map.size - 1][x]) && map[g_data.map.size
			- 1][x] != ' ')
			handle_map_error(BADWALLS);
	x = -1;
	while (map[g_data.map.size - 1][++x])
		if (map[g_data.map.size - 1][x] == ' ')
			find_wall(map, g_data.map.size - 1, x, -1);
}

static void	check_body(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[++y])
	{
		x = 0;
		while (map[y][++x])
		{
			if (is_floor(map[y][x]) && (!map[y + 1][x] || !map[y - 1][x]
					|| !map[y][x - 1] || !map[y][x + 1]))
				handle_map_error(BADWALLS);
			if (is_floor(map[y][x]) && (map[y][x - 1] == ' ' || map[y][x
					+ 1] == ' '))
				handle_map_error(BADWALLS);
			if (is_floor(map[y][x]) && (map[y - 1][x] == ' ' || map[y
					+ 1][x] == ' '))
				handle_map_error(BADWALLS);
			if (map[y][x] == ' ' && map[y][x - 1] != ' ' && !is_wall(map[y][x - 1]))
				handle_map_error(BADWALLS);
			if (map[y][x] == ' ')
				(find_wall(map, y, x, -1), find_wall(map, y, x, +1));
		}
	}
}

static void	initialize_map(void)
{
	int	i;
	int	j;

	i = 0;
	j = g_data.map.start_index;
	while (j <= g_data.map.end_index)
	{
		if (i == MAX_ROW)
			handle_map_error(BADMAP);
		g_data.map.map[i++] = ft_strtrim_end(g_data.file[j++], " \n\t\v\r\f");
	}
	g_data.map.map[i] = NULL;
	g_data.map.size = i;
	g_data.map.orientation = '\0';
}

void	check_map(void)
{
	initialize_map();
	check_top_bottom(g_data.map.map);
	check_body(g_data.map.map);
	check_borders(g_data.map.map);
	check_orientation(g_data.map.map);
}
