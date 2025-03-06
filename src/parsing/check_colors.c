/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:06:36 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/06 14:58:41 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

static void	check_double_colors(void)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 2)
	{
		j = g_data.colors[i].index + 1;
		while (g_data.file[j])
		{
			k = 0;
			while (is_whitespace(g_data.file[j][k]))
				k++;
			if (!ft_strncmp(&g_data.file[j][k], g_data.colors[i].material,
					1))
				handle_colors_error(DOUBLECOLORS);
			j++;
		}
		i++;
	}
}

static void	check_colors_after_map(void)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (g_data.colors[i].index >= g_data.map.start_index)
			handle_colors_error(MAPNOTEND);
		i++;
	}
}

static void	check_valid_colors(void)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (!g_data.colors[i].material)
			handle_colors_error(MISSINGCOLOR);
		if (g_data.colors[i].red < 0 || g_data.colors[i].red > 255)
			handle_colors_error(BADNUMBERCOLOR);
		if (g_data.colors[i].green < 0 || g_data.colors[i].green > 255)
			handle_colors_error(BADNUMBERCOLOR);
		if (g_data.colors[i].blue < 0 || g_data.colors[i].blue > 255)
			handle_colors_error(BADNUMBERCOLOR);
		i++;
	}
}

void	check_colors(void)
{
	initialize_colors();
	check_valid_colors();
	check_colors_after_map();
	check_double_colors();
}
