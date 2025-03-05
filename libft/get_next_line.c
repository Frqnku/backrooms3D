/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:09:23 by utiberto          #+#    #+#             */
/*   Updated: 2024/12/17 15:49:43 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_new_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_calloc((ft_strlen(stash) - i), sizeof(char));
	if (!new_stash)
		return (NULL);
	i += 1;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

static char	*extract_line_from_stash(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*read_and_stash(int fd, char *stash, int *read_bytes)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_calloc(2, sizeof(char));
	if (!buffer)
		return (NULL);
	while (*read_bytes > 0)
	{
		*read_bytes = read(fd, buffer, 1);
		if (*read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[*read_bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			read_bytes;

	read_bytes = 1;
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}
	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	stash = read_and_stash(fd, stash, &read_bytes);
	if (!stash || !stash[0])
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line_from_stash(stash);
	stash = get_new_stash(stash);
	return (line);
}
