/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:54:41 by utiberto          #+#    #+#             */
/*   Updated: 2024/11/14 14:13:16 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_max_size(const char *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[start + i])
		i++;
	if (i >= len)
		return (len);
	return (i);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			size;
	char			*sub;

	if (!s)
		return (0);
	if (start >= (unsigned int)ft_strlen(s))
	{
		sub = malloc(sizeof(char));
		sub[0] = '\0';
		return (sub);
	}
	i = 0;
	size = ft_get_max_size(s, start, len);
	sub = malloc(sizeof(char) * (size + 1));
	if (!sub)
		return (0);
	while (s[start + i] && i < (unsigned int)size)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
