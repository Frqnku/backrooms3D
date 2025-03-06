/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:56:18 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/06 16:31:04 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/* libc */
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int	    ft_isdigit(int c);
int	    is_whitespace(char c);
int     is_str_whitespace(char *str);


/* additional function */
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_count_words(const char *s, char c);
void	free_split(char **arr);
void	free_map(char **arr);
int	    get_tab_size(char **tab);
int		get_char_index(const char *s, char c);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strtrim_end(const char *s1, const char *set);

/* GNL */
char	*get_next_line(int fd);

#endif