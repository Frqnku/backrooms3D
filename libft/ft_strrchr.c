/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:50:41 by utiberto          #+#    #+#             */
/*   Updated: 2024/11/14 14:07:58 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = 0;
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			last = (char *)s;
		s++;
	}
	if (!(unsigned char)c)
		return ((char *)s);
	return (last);
}
