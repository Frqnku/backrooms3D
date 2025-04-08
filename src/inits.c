/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:16:06 by khadj-me          #+#    #+#             */
/*   Updated: 2025/04/08 16:55:03 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backrooms.h"

void init_textures()
{
	int i;

	i = 0;
	
	while (i < 4)
	{
		g_data.textures[i].spr = mlx_xpm_file_to_image(g_data.mlx, g_data.textures[i].path, &g_data.textures[i].width, &g_data.textures[i].height);
		if (g_data.textures[i].spr == NULL)
			destroy_game(&g_data); // do the xpm convert check in parsing check args
		g_data.textures[i].data = mlx_get_data_addr(g_data.textures[i].spr, &g_data.textures[i].bpp, &g_data.textures[i].size_line, &g_data.textures[i].endian);
		if (g_data.textures[i].data == NULL)
			destroy_game(&g_data);
		i++;
	}
}

void init_data(int ac, char **av)
{
	check_args(ac, av);
	find_spawn_coor();
	g_data.player.w = RELEASED;
	g_data.player.s = RELEASED;
	g_data.player.a = RELEASED;
	g_data.player.d = RELEASED;
	g_data.player.l_arr = RELEASED;
	g_data.player.r_arr = RELEASED;
	g_data.player.view = PI / 3 * 2;
	g_data.mlx = NULL;
	g_data.mlx_window = NULL;
	g_data.mlx_img = NULL;
	g_data.screen = NULL;
	g_data.bits_pr_pxl = 0;
	g_data.line_length = 0;
	g_data.endian = 0;
	g_data.mlx = mlx_init();
	if (!g_data.mlx)
		destroy_game(&g_data);
	g_data.mlx_window = mlx_new_window(g_data.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Backrooms 3D");
	if (!g_data.mlx_window)
		destroy_game(&g_data);
	g_data.mlx_img = mlx_new_image(g_data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!g_data.mlx_img)
		destroy_game(&g_data);
	g_data.screen = mlx_get_data_addr(g_data.mlx_img, &g_data.bits_pr_pxl, &g_data.line_length, &g_data.endian);	
	init_textures();
	mlx_put_image_to_window(g_data.mlx, g_data.mlx_window, g_data.mlx_img, 0, 0);
}