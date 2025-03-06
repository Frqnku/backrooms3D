/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:54:42 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/06 14:39:17 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"
#include <stdio.h>

static void	check_map_last(void)
{
	char	*last_line;
	int		i;

	i = 0;
	last_line = g_data.map.file[g_data.map.end_index];
	while (last_line[i])
	{
		if (last_line[i] != '1' && !is_whitespace(last_line[i]))
		{
			free_map(g_data.map.file);
			handle_error(MAPNOTEND);
		}
		i++;
	}
}

static int	find_map_start_index(void)
{
	int	i;

	i = g_data.map.end_index;
	while (i > 0)
	{
		if (is_str_whitespace(g_data.map.file[i]))
			return (i + 1);
		i--;
	}
	return (i);
}

static int	find_last_line_index(void)
{
	int	i;

	i = get_tab_size(g_data.map.file) - 1;
	while (i > 0)
	{
		if (!is_str_whitespace(g_data.map.file[i]))
			return (i);
		i--;
	}
	return (i);
}

static void	initialize_file(char *map)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		handle_error(BADREAD);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		g_data.map.file[i++] = ft_strdup(line);
		free(line);
		if (i == MAX_ROW)
			handle_file_error(BADFILE, fd);
		line = get_next_line(fd);
	}
	g_data.map.file[i] = NULL;
	g_data.map.end_index = find_last_line_index();
	g_data.map.start_index = find_map_start_index();
	close(fd);
}

void	check_map(char *map)
{
	initialize_file(map);
	check_map_last();
	check_textures();
	check_colors();
	check_file_chars();
}
