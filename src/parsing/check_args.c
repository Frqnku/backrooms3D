/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:21:21 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/05 17:09:54 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

static void	check_map_extension(char *map)
{
	char	*last_cub;

	if (!map)
		handle_error(NOCUB);
	if (ft_strlen(map) < 5)
		handle_error(NOCUB);
	last_cub = ft_strnstr(map, ".cub", ft_strlen(map));
	if (!last_cub)
		handle_error(NOCUB);
	if (ft_strlen(last_cub) != 4)
		handle_error(NOCUB);
}

void	check_args(int ac, char **av)
{
	if (ac == 1)
		handle_error(BADARG1);
	if (ac > 2)
		handle_error(BADARG2);
	check_map_extension(av[1]);
	check_map(av[1]);
	// int i = 0;
	// while (g_data.map.file[i])
	//     printf("%s", g_data.map.file[i++]);
}
