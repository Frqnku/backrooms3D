/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:31:23 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/06 16:30:48 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	size_t	start;
	size_t	last;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in_set(s1[start], set))
		start++;
	last = ft_strlen(s1);
	while (last > start && ft_is_in_set(s1[last - 1], set))
		last--;
	result = (char *)malloc(sizeof(char) * ((last - start) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (start < last)
		result[i++] = s1[start++];
	result[i] = '\0';
	return (result);
}

char	*ft_strtrim_end(const char *s1, const char *set)
{
	int		i;
	size_t	start;
	size_t	last;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	last = ft_strlen(s1);
	while (last > start && ft_is_in_set(s1[last - 1], set))
		last--;
	result = (char *)malloc(sizeof(char) * ((last - start) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (start < last)
		result[i++] = s1[start++];
	result[i] = '\0';
	return (result);
}