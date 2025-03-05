/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:26 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/05 17:05:48 by utiberto         ###   ########.fr       */
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
