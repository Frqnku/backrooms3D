/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:55:11 by utiberto          #+#    #+#             */
/*   Updated: 2024/12/07 15:53:20 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] == c && in_word)
			in_word = 0;
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*ft_dup(const char *s, char c, size_t *start, char **result)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = *start;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	*start = i;
	while (s[i] && s[i] != c)
		i++;
	str = malloc(sizeof(char) * ((i - *start) + 1));
	if (!str)
		free(result);
	while (*start < i)
	{
		str[j++] = ((char *)s)[*start];
		*start = *start + 1;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	char	*dup;
	size_t	start;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	while (i < len)
	{
		dup = ft_dup(s, c, &start, result);
		result[i++] = dup;
	}
	result[i] = NULL;
	return (result);
}
