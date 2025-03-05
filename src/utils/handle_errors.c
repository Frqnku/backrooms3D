/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:22:32 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/05 17:05:53 by utiberto         ###   ########.fr       */
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
	free_map(g_data.map.file);
	handle_error(err);
}

void	handle_textures_error(char *err)
{
	clean_textures_path();
	free_map(g_data.map.file);
	handle_error(err);
}

void	handle_gnl_error(char *err, char *line, int fd)
{
	close(fd);
	free(line);
	get_next_line(-1);
	handle_error(err);
}

void	handle_fd_error(char *err, int fd)
{
	close(fd);
	handle_error(err);
}
