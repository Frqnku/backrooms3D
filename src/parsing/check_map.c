/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:54:42 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/06 16:38:57 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"
#include <stdio.h>

static void find_wall(char **map, int y, int x, int offset)
{
	while (y >= 0 && y < g_data.map.size)
	{
		if ((int)ft_strlen(map[y]) <= x)
			y += offset;
		else if (map[y][x] == ' ')
			y += offset;
		else if (map[y][x] == '1')
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
		if (map[0][x] != '1' && map[0][x] != ' ')
			handle_map_error(BADWALLS);
	x = -1;
	while (map[0][++x])
		if (map[0][x] == ' ')
			find_wall(map, 0, x, +1);
	x = -1;
	while (map[g_data.map.size - 1][++x])
		if (map[g_data.map.size - 1][x] != '1' && map[g_data.map.size - 1][x] != ' ')
			handle_map_error(BADWALLS);
	x = -1;
	while (map[g_data.map.size - 1][++x])
		if (map[g_data.map.size - 1][x] == ' ')
			find_wall(map, g_data.map.size - 1, x, -1);
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
}

void	check_map(void)
{
	initialize_map();
	check_top_bottom(g_data.map.map);
}
