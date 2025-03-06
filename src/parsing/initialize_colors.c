/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:31:01 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/06 14:59:58 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

static void	parse_colors(t_color *color, char *str)
{
	int		i;
	int		j;
	char	**values;

	if (ft_count_words(str, ',') != 3)
		(free(str), handle_colors_error(BADCOLOR));
	values = ft_split(str, ',');
	free(str);
	i = -1;
	while (values[++i])
	{
		j = 0;
		if (!values[i][j])
			(free_split(values), handle_colors_error(BADCOLOR));
		while (values[i][j])
		{
			if (!ft_isdigit(values[i][j]) && !is_whitespace(values[i][j]))
				(free_split(values), handle_colors_error(BADCOLOR));
			j++;
		}
	}
	color->red = ft_atoi(values[0]);
	color->green = ft_atoi(values[1]);
	color->blue = ft_atoi(values[2]);
	free_split(values);
}

static t_color	add_color(char *material, int i, int j)
{
	t_color	color;
	char	*values;

	color.index = i;
	color.red = -1;
	color.green = -1;
	color.blue = -1;
	j += 1;
	while (is_whitespace(g_data.file[i][j]))
		j++;
	values = ft_strtrim(g_data.file[i] + j, " \n\t\v\r\f");
	parse_colors(&color, values);
	if (!ft_strncmp("F", material, 1))
		color.material = ft_strdup("F");
	if (!ft_strncmp("C", material, 1))
		color.material = ft_strdup("C");
	return (color);
}

static t_color	find_color(char *material)
{
	t_color	color;
	int		i;
	int		j;

	i = 0;
	color.material = NULL;
	color.red = -1;
	color.green = -1;
	color.blue = -1;
	color.index = -1;
	while (g_data.file[i])
	{
		j = 0;
		while (is_whitespace(g_data.file[i][j]))
			j++;
		if (!ft_strncmp(&g_data.file[i][j], material, 1))
		{
			color = add_color(material, i, j);
			break ;
		}
		i++;
	}
	return (color);
}

void	initialize_colors(void)
{
	g_data.colors[0] = find_color("F");
	g_data.colors[1] = find_color("C");
}