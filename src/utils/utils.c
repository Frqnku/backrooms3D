/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:42:01 by khadj-me          #+#    #+#             */
/*   Updated: 2025/04/10 14:34:19 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backrooms.h"

int	tblotbl_len(char **tbl)
{
	int	i;

	if (!tbl)
		return (0);
	i = 0;
	while (tbl[i] != NULL)
		i++;
	return (i);
}

int	is_in_charset(char c, const char *charset)
{
	if (!charset || !c)
		return (0);
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}
