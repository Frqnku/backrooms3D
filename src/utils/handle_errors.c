/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:22:32 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/06 16:32:20 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

void	handle_error(char *err)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err, 2);
	exit(1);
}

void	handle_file_error(char *err, int fd)
{
	close(fd);
	get_next_line(-1);
	free_map(g_data.file);
	handle_error(err);
}

void	handle_textures_error(char *err)
{
	clean_textures_path();
	free_map(g_data.file);
	handle_error(err);
}

void	handle_colors_error(char *err)
{
	clean_colors();
	handle_textures_error(err);
}

void	handle_map_error(char *err)
{
	free_map(g_data.map.map);
	handle_colors_error(err);
}
