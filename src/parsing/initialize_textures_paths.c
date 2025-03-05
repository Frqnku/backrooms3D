/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_textures_paths.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:43:05 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/05 17:05:45 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

static t_texture	add_texture(char *orientation, int i, int j)
{
	t_texture	texture;

	texture.index = i;
	texture.path = NULL;
	texture.orientation = NULL;
	j += 1;
	while (is_whitespace(g_data.map.file[i][j]))
		j++;
	texture.path = ft_strtrim(g_data.map.file[i] + j + 1, " \n\t\v\r\f");
	if (!ft_strncmp("NO", orientation, 2))
		texture.orientation = ft_strdup("NO");
	if (!ft_strncmp("SO", orientation, 2))
		texture.orientation = ft_strdup("SO");
	if (!ft_strncmp("WE", orientation, 2))
		texture.orientation = ft_strdup("WE");
	if (!ft_strncmp("EA", orientation, 2))
		texture.orientation = ft_strdup("EA");
	return (texture);
}

static t_texture	find_texture(char *orientation)
{
	t_texture	texture;
	int			i;
	int			j;

	i = 0;
	texture.path = NULL;
	texture.orientation = NULL;
	texture.index = -1;
	while (g_data.map.file[i])
	{
		j = 0;
		while (is_whitespace(g_data.map.file[i][j]))
			j++;
		if (!ft_strncmp(&g_data.map.file[i][j], orientation, 2))
		{
			texture = add_texture(orientation, i, j);
			break ;
		}
		i++;
	}
	return (texture);
}

void	initialize_textures_paths(void)
{
	g_data.textures[0] = find_texture("NO");
	g_data.textures[1] = find_texture("SO");
	g_data.textures[2] = find_texture("WE");
	g_data.textures[3] = find_texture("EA");
}
