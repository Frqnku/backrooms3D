/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:17:22 by khadj-me          #+#    #+#             */
/*   Updated: 2025/04/11 11:28:46 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backrooms.h"

int	destroy_game(t_data *data)
{
	cleanup();
	if (data->mlx)
	{
		if (data->mlx_img)
			mlx_destroy_image(data->mlx, data->mlx_img);
		if (data->mlx_window)
			mlx_destroy_window(data->mlx, data->mlx_window);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	}
	exit(1);
	return (0);
}

int	on_keypress(int input, t_data *data)
{
	if (input == KEY_ESC)
		destroy_game(data);
	if (input == KEY_W)
		data->player.w = PRESSED;
	if (input == KEY_S)
		data->player.s = PRESSED;
	if (input == KEY_A)
		data->player.a = PRESSED;
	if (input == KEY_D)
		data->player.d = PRESSED;
	if (input == ARROW_LEFT)
		data->player.l_arr = PRESSED;
	if (input == ARROW_RIGHT)
		data->player.r_arr = PRESSED;
	return (0);
}

int	on_keyrelease(int input, t_data *data)
{
	if (input == KEY_W)
		data->player.w = RELEASED;
	if (input == KEY_S)
		data->player.s = RELEASED;
	if (input == KEY_A)
		data->player.a = RELEASED;
	if (input == KEY_D)
		data->player.d = RELEASED;
	if (input == ARROW_LEFT)
		data->player.l_arr = RELEASED;
	if (input == ARROW_RIGHT)
		data->player.r_arr = RELEASED;
	return (0);
}
