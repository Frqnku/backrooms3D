/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:44:36 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/24 07:19:51 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

static void	check_map_last(void)
{
	char	*last_line;
	int		i;

	i = 0;
	last_line = g_data.file[g_data.map.end_index];
	while (last_line[i])
	{
		if (last_line[i] != '1' && !is_whitespace(last_line[i]))
		{
			free_map(g_data.file);
			if (last_line[i] == '0')
				handle_error(BADWALLS);
			else
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
		if (is_str_whitespace(g_data.file[i]))
			return (i + 1);
		i--;
	}
	return (i);
}

static int	find_last_line_index(void)
{
	int	i;

	i = get_tab_size(g_data.file) - 1;
	while (i > 0)
	{
		if (!is_str_whitespace(g_data.file[i]))
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
		g_data.file[i++] = ft_strdup(line);
		free(line);
		if (i == MAX_ROW)
			handle_file_error(BADFILE, fd);
		line = get_next_line(fd);
	}
	g_data.file[i] = NULL;
	g_data.map.end_index = find_last_line_index();
	g_data.map.start_index = find_map_start_index();
	close(fd);
}

void	check_file(char *map)
{
	initialize_file(map);
	check_map_last();
	check_textures();
	check_colors();
	check_file_chars();
}
