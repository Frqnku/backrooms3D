/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:10:42 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/08 14:24:27 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

void	check_orientation(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[++y])
	{
		x = 0;
		while (map[y][x] && !is_orientation(map[y][x]))
			x++;
		if (is_orientation(map[y][x]) && !g_data.map.orientation)
			g_data.map.orientation = map[y][x];
		else if (is_orientation(map[y][x]) && g_data.map.orientation)
			handle_map_error(DOUBLEORIENTATION);
	}
	if (!g_data.map.orientation)
		handle_map_error(NOORIENTATION);
}

void	check_borders(char **map)
{
	int	y;
	int	x;
	int	last;

	y = 0;
	while (map[++y])
	{
		last = ft_strlen(map[y]) - 1;
		x = 0;
		while (map[y][x] == ' ')
			x++;
		if (!is_wall(map[y][x]) || !is_wall(map[y][last]))
			handle_map_error(BADWALLS);
	}
}
