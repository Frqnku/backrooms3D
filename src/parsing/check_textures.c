/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:37:33 by utiberto          #+#    #+#             */
/*   Updated: 2025/04/03 09:13:36 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

static void	check_double_textures(void)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 4)
	{
		j = g_data.textures[i].index + 1;
		while (g_data.file[j])
		{
			k = 0;
			while (is_whitespace(g_data.file[j][k]))
				k++;
			if (!ft_strncmp(&g_data.file[j][k], g_data.textures[i].orientation,
				2))
				handle_textures_error(DOUBLETEXTURES);
			j++;
		}
		i++;
	}
}

static void	check_textures_after_map(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g_data.textures[i].index >= g_data.map.start_index)
			handle_textures_error(MAPNOTEND);
		i++;
	}
}

static void	check_texture_extension(char *texture)
{
	char	*last_xpm;

	if (!texture)
		handle_textures_error(MISSINGTEXTURE);
	if (ft_strlen(texture) < 5)
		handle_textures_error(NOXPM);
	last_xpm = ft_strnstr(texture, ".xpm", ft_strlen(texture));
	if (!last_xpm)
		handle_textures_error(NOXPM);
	if (ft_strlen(last_xpm) != 4)
		handle_textures_error(NOXPM);
}

static void	check_valid_textures(void)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		check_texture_extension(g_data.textures[i].path);
		fd = open(g_data.textures[i].path, O_RDONLY);
		if (fd == -1)
			handle_textures_error(BADTEXTURE);
		close(fd);
		i++;
	}
}

void	check_textures(void)
{
	initialize_textures_paths();
	check_valid_textures();
	check_textures_after_map();
	check_double_textures();
}
