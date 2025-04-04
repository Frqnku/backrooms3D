
#include "backrooms.h"

t_data g_data;

void put_pixel(int x, int y, int color)
{
	char *dst;
		
	dst = NULL;
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	dst = g_data.screen + (y * g_data.line_length + x * (g_data.bits_pr_pxl / 8));
	*(unsigned int *)dst = color;
}

int main()
{
	int textures[4][sizeof(int) * 32 * 32];
	int x = 32;
	int y = 32;
	g_data.mlx = mlx_init();
    if (!g_data.mlx)
		exit(1);
	g_data.mlx_window = mlx_new_window(g_data.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Backrooms 3D");
	if (!g_data.mlx_window)
		exit(1);
	g_data.mlx_img = mlx_new_image(g_data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!g_data.mlx_img)
		exit(1);
	g_data.screen = mlx_get_data_addr(g_data.mlx_img, &g_data.bits_pr_pxl, &g_data.line_length, &g_data.endian);	
	mlx_put_image_to_window(g_data.mlx, g_data.mlx_window, g_data.mlx_img, 0, 0);
	g_data.textures[0].spr = mlx_xpm_file_to_image(g_data.mlx, "./textures/player_spr_backward.xpm", &x, &y);
	g_data.textures[0].path = mlx_get_data_addr(g_data.textures[0].spr, &g_data.textures[0].bits_pr_pxl, &g_data.textures[0].line_length, &g_data.textures[0].endian);
	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 32; j++)
			put_pixel(j + 50, i + 50, *(int *)(g_data.textures[0].path + (i * g_data.textures[0].line_length + j * (g_data.textures[0].bits_pr_pxl / 8))));
	mlx_put_image_to_window(g_data.mlx, g_data.mlx_window, g_data.mlx_img, 0, 0);
	mlx_loop(g_data.mlx);
}