/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:03:38 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/06 16:32:41 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		if (arr[i])
			free(arr[i++]);
	if (arr)
		free(arr);
}

void	free_map(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		if (arr[i])
			free(arr[i++]);
}
