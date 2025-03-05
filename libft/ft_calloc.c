/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:39:52 by utiberto          #+#    #+#             */
/*   Updated: 2024/11/11 17:30:59 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	size_t			total_size;
	unsigned char	*result;

	i = 0;
	total_size = size * nmemb;
	if (!nmemb || !size)
		return (malloc(0));
	if ((int)nmemb < 0 || (int)size < 0)
		return (0);
	result = malloc(total_size);
	if (!result)
		return (0);
	while (i < total_size)
		result[i++] = 0;
	return (result);
}
