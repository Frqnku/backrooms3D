/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:21:21 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/06 14:49:37 by utiberto         ###   ########.fr       */
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
