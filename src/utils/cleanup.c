/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:29:00 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/05 17:05:51 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"
#include <stdio.h>

void	clean_textures_path(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
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
	free_map(g_data.map.file);
}
