/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:16:06 by khadj-me          #+#    #+#             */
/*   Updated: 2025/04/11 15:47:18 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backrooms.h"

static void	init_view(int i, int j, char **map)
{
	if (map[i][j] == 'N')
		g_data.player.view = (PI / 2) * 3;
	else if (map[i][j] == 'S')
		g_data.player.view = PI / 2;
	else if (map[i][j] == 'E')
		g_data.player.view = 0;
	else if (map[i][j] == 'W')
		g_data.player.view = PI;
}

void	find_spawn_coor(void)
{
	char	**map;
	int		i;
	int		j;
	int		len;

	map = g_data.map.map;
	i = -1;
	j = -1;
	len = tblotbl_len(map);
	while (++i < len)
	{
		while (++j < (int)ft_strlen(map[i]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				g_data.player.coor[X] = j * TILE_SIZE + TILE_SIZE / 2;
				g_data.player.coor[Y] = i * TILE_SIZE + TILE_SIZE / 2;
				init_view(i, j, map);
				break ;
			}
		}
		j = -1;
	}
}

void	init_textures(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		g_data.textures[i].spr = mlx_xpm_file_to_image(g_data.mlx,
				g_data.textures[i].path, &g_data.textures[i].width,
				&g_data.textures[i].height);
		if (g_data.textures[i].spr == NULL)
		{
			ft_putendl_fd("Error: couldnt load xpm file", 2);
			destroy_game(&g_data);
		}
		g_data.textures[i].data = mlx_get_data_addr(g_data.textures[i].spr,
				&g_data.textures[i].bpp, &g_data.textures[i].size_line,
				&g_data.textures[i].endian);
		if (g_data.textures[i].data == NULL)
			destroy_game(&g_data);
		i++;
	}
}

void	basic_inits(void)
{
	g_data.player.w = RELEASED;
	g_data.player.s = RELEASED;
	g_data.player.a = RELEASED;
	g_data.player.d = RELEASED;
	g_data.player.l_arr = RELEASED;
	g_data.player.r_arr = RELEASED;
	g_data.mlx = NULL;
	g_data.mlx_window = NULL;
	g_data.mlx_img = NULL;
	g_data.screen = NULL;
	g_data.bits_pr_pxl = 0;
	g_data.line_length = 0;
	g_data.endian = 0;
	g_data.mlx = mlx_init();
}

void	init_data(int ac, char **av)
{
	check_args(ac, av);
	find_spawn_coor();
	basic_inits();
	if (!g_data.mlx)
		destroy_game(&g_data);
	init_textures();
	g_data.mlx_window = mlx_new_window(g_data.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Backrooms 3D");
	if (!g_data.mlx_window)
		destroy_game(&g_data);
	g_data.mlx_img = mlx_new_image(g_data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!g_data.mlx_img)
		destroy_game(&g_data);
	g_data.screen = mlx_get_data_addr(g_data.mlx_img, &g_data.bits_pr_pxl,
			&g_data.line_length, &g_data.endian);
	mlx_put_image_to_window(g_data.mlx, g_data.mlx_window, g_data.mlx_img, 0,
		0);
}
