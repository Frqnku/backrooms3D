/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:34:34 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/05 17:56:48 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

static int	is_texture_index(int i)
{
	int	j;

	j = 0;
	while (j < 4)
	{
		if (i == g_data.textures[j].index)
			return (1);
		j++;
	}
	return (0);
}

void	check_file_chars(void)
{
	int i;

	i = -1;
	while (++i < g_data.map.start_index)
	{
		if (is_texture_index(i))
			continue ;
		if (!is_str_whitespace(g_data.map.file[i]))
			handle_textures_error(BADFILECHAR);
	}
}