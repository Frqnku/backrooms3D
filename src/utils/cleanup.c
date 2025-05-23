/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:29:00 by utiberto          #+#    #+#             */
/*   Updated: 2025/04/10 12:09:26 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

void	clean_colors(void)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (g_data.colors[i].material)
			free(g_data.colors[i].material);
		i++;
	}
}

void	clean_textures_path(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g_data.textures[i].spr != NULL)
			mlx_destroy_image(g_data.mlx, g_data.textures[i].spr);
		if (g_data.textures[i].path)
			free(g_data.textures[i].path);
		if (g_data.textures[i].orientation)
			free(g_data.textures[i].orientation);
		i++;
	}
}

void	cleanup(void)
{
	clean_textures_path();
	clean_colors();
	free_map(g_data.file);
	free_map(g_data.map.map);
}
