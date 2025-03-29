/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:21:21 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/29 14:50:55 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

static void	check_file_extension(char *file)
{
	char	*last_cub;

	if (!file)
		handle_error(NOCUB);
	if (ft_strlen(file) < 5)
		handle_error(NOCUB);
	last_cub = ft_strnstr(file, ".cub", ft_strlen(file));
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
	check_file_extension(av[1]);
	check_file(av[1]);
	check_map();
}
