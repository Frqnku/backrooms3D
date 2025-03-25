/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:26 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/24 07:34:20 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backrooms.h"
#include <stdio.h>

t_data	g_data;

int	main(int ac, char **av)
{
	check_args(ac, av);
	cleanup();
}
