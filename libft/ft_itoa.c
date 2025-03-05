/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:07:23 by utiberto          #+#    #+#             */
/*   Updated: 2024/11/14 11:42:09 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_buffer_size(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*handle_minimal_int(void)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * 12);
	if (!result)
		return (0);
	i = 0;
	while (i < 11)
	{
		result[i] = "-2147483648"[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static void	fill_result(char *result, int size, int n, int sign)
{
	if (sign < 0)
	{
		result[0] = '-';
		result[size] = '\0';
		while (size > 1)
		{
			result[--size] = ((n % 10) + 48);
			n /= 10;
		}
	}
	else
	{
		result[size] = '\0';
		while (size > 0)
		{
			result[--size] = ((n % 10) + 48);
			n /= 10;
		}
	}
}

char	*ft_itoa(int n)
{
	int		size;
	int		sign;
	char	*result;

	if (n == -2147483648)
		return (handle_minimal_int());
	sign = n;
	if (n < 0)
		n *= -1;
	size = get_buffer_size(n);
	if (sign < 0)
		size += 1;
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (0);
	fill_result(result, size, n, sign);
	return (result);
}
